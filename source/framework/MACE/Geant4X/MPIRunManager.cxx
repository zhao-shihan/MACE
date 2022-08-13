#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Geant4X/MPIRunManager.hxx"
#include "MACE/Geant4X/MPIRunMessenger.hxx"
#include "MACE/Utility/Math/IntegerPower.hxx"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICall.hxx"
#include "MACE/Utility/MPIUtil/MPIRandomUtil.hxx"

#include "G4Exception.hh"
#include "G4Run.hh"
#include "Randomize.hh"

#include "mpi.h"

namespace MACE::Geant4X {

using MACE::Utility::Math::Pow2;

namespace Internal {

FlipG4cout::FlipG4cout() {
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.IsWorker() or
        mpiEnv.GetVerboseLevel() == Environment::VerboseLevel::Quiet) {
        static ObserverPtr<std::streambuf> gG4coutBufExchanger = nullptr;
        gG4coutBufExchanger = G4cout.rdbuf(gG4coutBufExchanger);
    }
}

} // namespace Internal

MPIRunManager::MPIRunManager() :
    Internal::PreG4RunManagerInitFlipG4cout(),
    G4RunManager(),
    Internal::PostG4RunManagerInitFlipG4cout(),
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
    MPIRunMessenger::Instance().SetTo(this);
}

void MPIRunManager::SetPrintProgress(G4int val) {
    printModulo = -1;
    fPrintProgress = val;
}

void MPIRunManager::BeamOn(G4int nEvent, const char* macroFile, G4int nSelect) {
    if (CheckNEventIsAtLeastCommSize(nEvent)) {
        Utility::MPIUtil::MPIReSeedCLHEPRandom(G4Random::getTheEngine());
        fTotalNumberOfEventsToBeProcessed = nEvent;
        const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        fEventIDRange = Utility::MPIUtil::AllocMPIJobsJobWise(0, nEvent, mpiEnv.GetWorldSize(), mpiEnv.GetWorldRank());
        G4RunManager::BeamOn(fEventIDRange.count, macroFile, nSelect);
    }
}

void MPIRunManager::RunInitialization() {
    // wait for everyone to start
    MACE_CHECKED_MPI_CALL(MPI_Barrier,
                          MPI_COMM_WORLD)
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
    MACE_CHECKED_MPI_CALL(MPI_Barrier,
                          MPI_COMM_WORLD)
    // run end report
    RunEndReport();
}

G4bool MPIRunManager::CheckNEventIsAtLeastCommSize(G4int nEvent) const {
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        nEvent < mpiEnv.GetWorldSize()) {
        if (mpiEnv.IsMaster()) {
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
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.IsMaster() and fPrintProgress >= 0) {
        const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(mpiEnv.GetVerboseLevel(), Error, G4cout)
            << "--------------------------------> Run Starts <--------------------------------\n"
            << std::put_time(std::localtime(&now), "%c (UTC%z) > Run ") << runIDCounter << " starts on " << mpiEnv.GetWorldSize() << " ranks.\n"
            << "--------------------------------> Run Starts <--------------------------------" << G4endl;
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
        const auto precisionOfG4cout = G4cout.precision(3); // P.S. The precision of G4cout must be changed somewhere in G4, however inexplicably not changed back. We leave it as is.
        const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(mpiEnv.GetVerboseLevel(), Error, G4cout)
            << std::put_time(std::localtime(&now), "%c (UTC%z) > Event ") << endedEventID << " finished in rank " << mpiEnv.GetWorldRank() << ".\n"
            << "  ETA: " << eta << " +/- " << etaError << " s. Progress of the rank: " << numberOfEventProcessed << '/' << numberOfEventToBeProcessed << " (" << 100 * (float)numberOfEventProcessed / (float)numberOfEventToBeProcessed << "%)." << G4endl;
        G4cout.precision(precisionOfG4cout);
    }
}

void MPIRunManager::RunEndReport() const {
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.IsMaster() and fPrintProgress >= 0) {
        const auto endedRunID = runIDCounter - 1;
        const auto beginTime = std::chrono::system_clock::to_time_t(fRunBeginSystemTime);
        const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(mpiEnv.GetVerboseLevel(), Error, G4cout)
            << "-------------------------------> Run Finished <-------------------------------\n"
            << std::put_time(std::localtime(&now), "%c (UTC%z) > Run ") << endedRunID << " finished on " << mpiEnv.GetWorldSize() << " ranks.\n"
            << "  Start time: " << std::put_time(std::localtime(&beginTime), "%c (UTC%z).\n")
            << "   Wall time: " << fRunWallTime.count() << " s.\n"
            << "-------------------------------> Run Finished <-------------------------------" << G4endl;
    }
}

} // namespace MACE::Geant4X
