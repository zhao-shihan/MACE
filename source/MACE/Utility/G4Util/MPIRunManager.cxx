#include "MACE/Utility/G4Util/CheckMPIAvailability.hxx"
#include "MACE/Utility/G4Util/MPIRunManager.hxx"
#include "MACE/Utility/G4Util/MPIRunMessenger.hxx"
#include "MACE/Utility/Math/IntegerPower.hxx"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.hxx"
#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"
#include "MACE/Utility/MPIUtil/MPIRandomUtil.hxx"

#include "G4Exception.hh"
#include "G4Run.hh"
#include "Randomize.hh"

#include "mpi.h"

namespace MACE::Utility::G4Util {

using namespace MACE::Utility::MPIUtil;
using MACE::Utility::Math::Pow2;

namespace Detail {

MPIRunManagerInitializeHelper::MPIRunManagerInitializeHelper() {
    if (MPICommRank(MPI_COMM_WORLD) != 0) {
        FlipG4cout();
    }
}

void MPIRunManagerInitializeHelper::PrintStartupMessage() {
    if (MPICommRank(MPI_COMM_WORLD) == 0) {
        G4cout << " Running on " << MPICommSize(MPI_COMM_WORLD) << " processes.\n\n"
               << "**************************************************************\n"
               << G4endl;
    } else {
        FlipG4cout();
    }
}

void MPIRunManagerInitializeHelper::FlipG4cout() {
    static ObserverPtr<std::streambuf> fgG4coutBufKeeper = nullptr;
    fgG4coutBufKeeper = G4cout.rdbuf(fgG4coutBufKeeper);
}

} // namespace Detail

MPIRunManager::MPIRunManager() :
    Detail::MPIRunManagerInitializeHelper(),
    G4RunManager(),
    fCommRank((CheckMPIAvailability(), MPICommRank(MPI_COMM_WORLD))),
    fCommSize(MPICommSize(MPI_COMM_WORLD)),
    fTotalNumberOfEventsToBeProcessed(0),
    fEventIDRange(),
    fEventIDCounter(-1),
    fPrintProgress(-1),
    fRunBeginSystemTime(),
    fRunBeginWallTime(),
    fRunBeginCPUTime(0),
    fEventBeginWallTime(),
    fEventWallTime(),
    fNAvgEventWallTime(0),
    fNDevEventWallTime(std::numeric_limits<decltype(fNDevEventWallTime)>::epsilon()),
    fRunWallTime(),
    fRunCPUTime(0) {
    PrintStartupMessage();
    MPIRunMessenger::Instance().SetTo(this);
}

void MPIRunManager::SetPrintProgress(G4int val) {
    printModulo = -1;
    fPrintProgress = val;
}

void MPIRunManager::BeamOn(G4int nEvent, const char* macroFile, G4int nSelect) {
    CheckMPIAvailability();
    if (CheckNEventIsAtLeastCommSize(nEvent)) {
        MPIReSeedCLHEPRandom(G4Random::getTheEngine());
        fTotalNumberOfEventsToBeProcessed = nEvent;
        fEventIDRange = AllocMPIJobsJobWise(0, nEvent, fCommSize, fCommRank);
        G4RunManager::BeamOn(fEventIDRange.count, macroFile, nSelect);
    }
}

void MPIRunManager::RunInitialization() {
    // wait for everyone to start
    MPI_Barrier(MPI_COMM_WORLD);
    // start the run timer
    fRunBeginSystemTime = std::chrono::system_clock::now();
    fRunBeginWallTime = std::chrono::steady_clock::now();
    fRunBeginCPUTime = std::clock();
    // initialize run
    G4RunManager::RunInitialization();
    // report
    RunBeginReport();
}

void MPIRunManager::InitializeEventLoop(G4int nEvent, const char* macroFile, G4int nSelect) {
    // reset event time statistic
    fNAvgEventWallTime = 0;
    fNDevEventWallTime = std::numeric_limits<decltype(fNDevEventWallTime)>::epsilon();
    // initialize event loop
    fEventIDCounter = fEventIDRange.begin;
    G4RunManager::InitializeEventLoop(nEvent, macroFile, nSelect);
}

void MPIRunManager::ProcessOneEvent(G4int) {
    // start the event timer
    fEventBeginWallTime = std::chrono::steady_clock::now();
    // process the event
    G4RunManager::ProcessOneEvent(fEventIDCounter);
}

void MPIRunManager::TerminateOneEvent() {
    // terminate the event
    G4RunManager::TerminateOneEvent();
    fEventIDCounter += fEventIDRange.step;
    // stop the event timer
    fEventWallTime = std::chrono::steady_clock::now() - fEventBeginWallTime;
    fNAvgEventWallTime += fEventWallTime.count();
    fNDevEventWallTime += Pow2(fEventWallTime.count() - fNAvgEventWallTime / numberOfEventProcessed);
    // report
    EventEndReport();
}

void MPIRunManager::RunTermination() {
    // terminate the run
    G4RunManager::RunTermination();
    // stop the run timer
    fRunWallTime = std::chrono::steady_clock::now() - fRunBeginWallTime;
    fRunCPUTime = std::clock() - fRunBeginCPUTime;
    // wait for everyone to finish
    MPI_Barrier(MPI_COMM_WORLD);
    // run end report
    RunEndReport();
}

G4bool MPIRunManager::CheckNEventIsAtLeastCommSize(G4int nEvent) const {
    if (nEvent < fCommSize) {
        if (fCommRank == 0) {
            G4Exception("MACE::Utility::G4Util::MPIRunManager::CheckNEventIsAtLeastCommSize(...)",
                        "TooFewNEventOrTooMuchRank",
                        JustWarning,
                        "The number of G4Event must be greater or equal to the number of MPI ranks,\n"
                        "otherwise deadlock could raise in execution code.\n"
                        "Please be careful.");
        }
        return false;
    } else {
        return true;
    }
}

void MPIRunManager::RunBeginReport() const {
    if (fCommRank == 0 and fPrintProgress >= 0) {
        const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        G4cout << "----------------------------> Run Starts <----------------------------\n"
               << std::put_time(std::localtime(&now), "%c (UTC%z) > Run ") << runIDCounter << " starts on " << fCommSize << " ranks.\n"
               << "----------------------------> Run Starts <----------------------------" << G4endl;
    }
}

void MPIRunManager::EventEndReport() const {
    if (fPrintProgress <= 0) { return; }
    const auto endedEventID = fEventIDCounter - fEventIDRange.step;
    if (endedEventID % fPrintProgress == 0) {
        const auto avgEventWallTime = fNAvgEventWallTime / numberOfEventProcessed;
        const auto nEventRemain = numberOfEventToBeProcessed - numberOfEventProcessed;
        const auto eta = avgEventWallTime * nEventRemain;
        const auto etaError = 1.959963984540054 * std::sqrt(fNDevEventWallTime / (numberOfEventProcessed - 1)) * nEventRemain; // 95% C.L. (assuming gaussian)
        const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const auto precisionOfG4cout = G4cout.precision(); // P.S. The precision of G4cout must be changed somewhere in G4, however inexplicably not changed back. We leave it as is.
        G4cout << std::setprecision(3)
               << std::put_time(std::localtime(&now), "%c (UTC%z) > Event ") << endedEventID << " finished in rank " << fCommRank << ".\n"
               << "  ETA: " << eta << " +/- " << etaError << " s. Progress of the rank: " << numberOfEventProcessed << '/' << numberOfEventToBeProcessed << " (" << 100 * (float)numberOfEventProcessed / (float)numberOfEventToBeProcessed << "%)." << G4endl
               << std::setprecision(precisionOfG4cout);
    }
}

void MPIRunManager::RunEndReport() const {
    if (fCommRank == 0 and fPrintProgress >= 0) {
        const auto endedRunID = runIDCounter - 1;
        const auto beginTime = std::chrono::system_clock::to_time_t(fRunBeginSystemTime);
        const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        G4cout << "---------------------------> Run Finished <---------------------------\n"
               << std::put_time(std::localtime(&now), "%c (UTC%z) > Run ") << endedRunID << " finished on " << fCommSize << " ranks.\n"
               << "  Start time: " << std::put_time(std::localtime(&beginTime), "%c (UTC%z).\n")
               << "   Wall time: " << fRunWallTime.count() << " s.\n"
               << "---------------------------> Run Finished <---------------------------" << G4endl;
    }
}

} // namespace MACE::Utility::G4Util
