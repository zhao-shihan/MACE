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

#include <array>
#include <charconv>
#include <cstdlib>
#include <string>

namespace MACE::Geant4X {

using MACE::Utility::Math::Pow2;

namespace internal {

FlipG4cout::FlipG4cout() {
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.IsWorker() or
        mpiEnv.GetVerboseLevel() == Environment::VerboseLevel::Quiet) {
        static ObserverPtr<std::streambuf> gG4coutBufExchanger = nullptr;
        gG4coutBufExchanger = G4cout.rdbuf(gG4coutBufExchanger);
    }
}

} // namespace internal

MPIRunManager::MPIRunManager() :
    internal::PreG4RunManagerInitFlipG4cout(),
    G4RunManager(),
    internal::PostG4RunManagerInitFlipG4cout(),
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
    if (fPrintProgress >= 0) {
        RunBeginReport(runIDCounter);
    }
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
    const auto endedEvent = fEventIDCounter;
    fEventIDCounter += fEventIDRange.step;
    // stop the event timer
    fEventWallTime = std::chrono::steady_clock::now() - fEventBeginWallTime;
    fNAvgEventWallTime += fEventWallTime.count();
    fNDevEventWallTime += Pow2(fEventWallTime.count() - fNAvgEventWallTime / numberOfEventProcessed);
    // report
    if (fPrintProgress > 0 and endedEvent % fPrintProgress == 0) {
        EventEndReport(endedEvent);
    }
}

void MPIRunManager::RunTermination() {
    // terminate the run
    const auto endedRun = runIDCounter;
    G4RunManager::RunTermination();
    // stop the run timer
    fRunWallTime = std::chrono::steady_clock::now() - fRunBeginWallTime;
    fRunCPUTime = std::clock() - fRunBeginCPUTime;
    // wait for everyone to finish
    MACE_CHECKED_MPI_CALL(MPI_Barrier,
                          MPI_COMM_WORLD)
    // run end report
    if (fPrintProgress >= 0) {
        RunEndReport(endedRun);
    }
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

void MPIRunManager::EventEndReport(G4int event) const {
    const auto& mpiEnv = Environment::MPIEnvironment::Instance();
    if (mpiEnv.GetVerboseLevel() < Environment::VerboseLevel::Error) { return; }
    const auto avgEventWallTime = fNAvgEventWallTime / numberOfEventProcessed;
    const auto nEventRemain = numberOfEventToBeProcessed - numberOfEventProcessed;
    const auto eta = FormatSecondToDHMS(std::lround(avgEventWallTime * nEventRemain));
    const auto etaError = numberOfEventProcessed == 1 ?
                              std::string("N/A") :
                              FormatSecondToDHMS(std::lround(1.959963984540054 * std::sqrt(fNDevEventWallTime / (numberOfEventProcessed - 1)) * nEventRemain)); // 95% C.L. (assuming gaussian)
    const auto progress = 100 * static_cast<double>(numberOfEventProcessed) / numberOfEventToBeProcessed;
    const auto precisionOfG4cout = G4cout.precision(6); // P.S. The precision of G4cout must be changed somewhere in G4, however inexplicably not changed back. We leave it as is.
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    G4cout << std::put_time(std::localtime(&now), "%c (UTC%z) > Event ") << event << " finished in rank " << mpiEnv.GetWorldRank() << ".\n"
           << "  ETA: " << eta << " +/- " << etaError << ". Progress of the rank: " << numberOfEventProcessed << '/' << numberOfEventToBeProcessed << " (" << progress << "%)." << G4endl;
    G4cout.precision(precisionOfG4cout);
}

void MPIRunManager::RunEndReport(G4int run) const {
    const auto& mpiEnv = Environment::MPIEnvironment::Instance();
    if (mpiEnv.IsWorker() or mpiEnv.GetVerboseLevel() < Environment::VerboseLevel::Error) { return; }
    const auto beginTime = std::chrono::system_clock::to_time_t(fRunBeginSystemTime);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    G4cout << "-------------------------------> Run Finished <-------------------------------\n"
           << std::put_time(std::localtime(&now), "%c (UTC%z) > Run ") << run << " finished on " << mpiEnv.GetWorldSize() << " ranks.\n"
           << "  Start time: " << std::put_time(std::localtime(&beginTime), "%c (UTC%z).\n")
           << "   Wall time: " << fRunWallTime.count() << " s.\n"
           << "-------------------------------> Run Finished <-------------------------------" << G4endl;
}

void MPIRunManager::RunBeginReport(G4int run) {
    const auto& mpiEnv = Environment::MPIEnvironment::Instance();
    if (mpiEnv.IsWorker() or mpiEnv.GetVerboseLevel() < Environment::VerboseLevel::Error) { return; }
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    G4cout << "--------------------------------> Run Starts <--------------------------------\n"
           << std::put_time(std::localtime(&now), "%c (UTC%z) > Run ") << run << " starts on " << mpiEnv.GetWorldSize() << " ranks.\n"
           << "--------------------------------> Run Starts <--------------------------------" << G4endl;
}

std::string MPIRunManager::FormatSecondToDHMS(long secondsInTotal) {
    const auto div86400 = std::div(secondsInTotal, 86400L);
    const auto div3600 = std::div(div86400.rem, 3600L);
    const auto div60 = std::div(div3600.rem, 60L);
    const auto& [day, hour, minute, second] = std::tie(div86400.quot, div3600.quot, div60.quot, div60.rem);
    const auto addDay = day > 0;
    const auto addHour = addDay or hour > 0;
    const auto addMinute = addDay or addHour or minute > 0;

    std::array<char, std::numeric_limits<long>::digits10 + 3> buffer; // long enough to store a "long"
    const auto bufferFirst = buffer.data();
    const auto bufferLast = buffer.data() + buffer.size();
    std::string dhms;
    if (addDay) {
        const auto charLast = std::to_chars(bufferFirst, bufferLast, day).ptr;
        dhms.append(std::string_view(bufferFirst, charLast)).append("d ");
    }
    if (addHour) {
        const auto charLast = std::to_chars(bufferFirst, bufferLast, hour).ptr;
        dhms.append(std::string_view(bufferFirst, charLast)).append("h ");
    }
    if (addMinute) {
        const auto charLast = std::to_chars(bufferFirst, bufferLast, minute).ptr;
        dhms.append(std::string_view(bufferFirst, charLast)).append("m ");
    }
    const auto charLast = std::to_chars(bufferFirst, bufferLast, second).ptr;
    dhms.append(std::string_view(bufferFirst, charLast)).append("s");
    return dhms;
}

} // namespace MACE::Geant4X
