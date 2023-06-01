#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/MPIRunManager.h++"
#include "MACE/Extension/Geant4X/MPIRunMessenger.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.h++"
#include "MACE/Utility/MPIUtil/MPIReseedPRNG.h++"

#include "G4Exception.hh"
#include "G4Run.hh"
#include "Randomize.hh"

#include "mpi.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <string>

namespace MACE::inline Extension::Geant4X {

namespace internal {

FlipG4cout::FlipG4cout() {
    if (const auto& mpiEnv = Env::MPIEnv::Instance();
        mpiEnv.AtCommWorldWorker() or
        mpiEnv.GetVerboseLevel() == Env::VerboseLevel::Quiet) {
        static std::streambuf* gG4coutBufExchanger = nullptr;
        gG4coutBufExchanger = G4cout.rdbuf(gG4coutBufExchanger);
    }
}

} // namespace internal

MPIRunManager::MPIRunManager() :
    internal::PreG4RunManagerInitFlipG4cout(),
    G4RunManager(),
    internal::PostG4RunManagerInitFlipG4cout(),
    fNEventToBeMPIProcessed(0),
    fEventIDRange{-1, -1, 0, 0},
    fPrintProgressModulo(Env::MPIEnv::Instance().Sequential() ? 1 : Env::MPIEnv::Instance().CommWorldSize() + 1),
    fEventWallTimeStopwatch(),
    fEventWallTime(0),
    fNAvgEventWallTime(0),
    fNDevEventWallTime(0),
    fRunCPUTimeStopwatch(),
    fRunCPUTime(0),
    fRunWallTimeStopwatch(),
    fRunWallTime(0),
    fRunBeginSystemTime(),
    fRunEndSystemTime() {
    MPIRunMessenger::Instance().AssignTo(this);
}

void MPIRunManager::BeamOn(G4int nEvent, gsl::czstring macroFile, G4int nSelect) {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (nEvent < mpiEnv.CommWorldSize()) {
        if (mpiEnv.AtCommWorldMaster()) {
            G4Exception("MACE::Utility::G4Util::MPIRunManager::CheckNEventIsAtLeastCommSize(...)",
                        "TooFewNEventOrTooMuchRank",
                        JustWarning,
                        "The number of G4Event must be greater or equal to the number of MPI ranks,\n"
                        "otherwise deadlock could raise in execution code.\n"
                        "Please be careful.");
        }
        return;
    }

    MPIUtil::MPIReseedPRNG(*G4Random::getTheEngine());
    fNEventToBeMPIProcessed = nEvent;
    fEventIDRange = MPIUtil::AllocMPIJobsJobWise(0, nEvent, mpiEnv.CommWorldSize(), mpiEnv.CommWorldRank());
    G4RunManager::BeamOn(fEventIDRange.count, macroFile, nSelect);
}

void MPIRunManager::RunInitialization() {
    // wait for everyone to start
    MACE_MPI_CALL_WITH_CHECK(MPI_Barrier,
                             MPI_COMM_WORLD)
    // start the run stopwatch
    fRunBeginSystemTime = std::chrono::system_clock::now();
    fRunCPUTimeStopwatch.Reset();
    fRunWallTimeStopwatch.Reset();
    // initialize run
    G4RunManager::RunInitialization();
    // report
    if (fPrintProgressModulo >= 0) {
        RunBeginReport(runIDCounter);
    }
}

void MPIRunManager::InitializeEventLoop(G4int nEvent, gsl::czstring macroFile, G4int nSelect) {
    // initialize event loop
    G4RunManager::InitializeEventLoop(nEvent, macroFile, nSelect);
    // reset event time statistic
    fNAvgEventWallTime = 0;
    fNDevEventWallTime = 0;
    // restart the event stopwatch just before the first event begins
    fEventWallTimeStopwatch.Reset();
}

void MPIRunManager::ProcessOneEvent(G4int iEvent) {
    G4RunManager::ProcessOneEvent(fEventIDRange.begin + iEvent * fEventIDRange.step);
}

void MPIRunManager::TerminateOneEvent() {
    // the terminating event ID
    const auto terminatedEventID = currentEvent->GetEventID();
    // terminate the event
    G4RunManager::TerminateOneEvent();
    // read & restart the event stopwatch
    fEventWallTime = fEventWallTimeStopwatch.SecondsElapsed();
    fEventWallTimeStopwatch.Reset();
    fNAvgEventWallTime += fEventWallTime;
    fNDevEventWallTime += Math::Pow2(fEventWallTime - fNAvgEventWallTime / numberOfEventProcessed);
    // report
    if (fPrintProgressModulo > 0 and terminatedEventID % fPrintProgressModulo == 0) {
        EventEndReport(terminatedEventID);
    }
}

void MPIRunManager::RunTermination() {
    // terminate the run
    const auto endedRun = runIDCounter;
    G4RunManager::RunTermination();
    // stop the run stopwatch
    fRunWallTime = fRunWallTimeStopwatch.SecondsElapsed();
    fRunCPUTime = fRunCPUTimeStopwatch.SecondsUsed();
    // wait for everyone to finish
    MACE_MPI_CALL_WITH_CHECK(MPI_Barrier,
                             MPI_COMM_WORLD)
    // run end report
    if (fPrintProgressModulo >= 0) {
        RunEndReport(endedRun);
    }
}

void MPIRunManager::EventEndReport(const G4int eventID) const {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (mpiEnv.GetVerboseLevel() < Env::VerboseLevel::Error) { return; }
    const auto avgEventWallTime = fNAvgEventWallTime / numberOfEventProcessed;
    const auto nEventRemain = numberOfEventToBeProcessed - numberOfEventProcessed;
    const auto eta = FormatSecondToDHMS(avgEventWallTime * nEventRemain);
    const auto etaError = numberOfEventProcessed < 5 ?
                              std::string("N/A") :
                              FormatSecondToDHMS(1.96 * std::sqrt(fNDevEventWallTime / (numberOfEventProcessed - 1) * nEventRemain)); // 95% C.L. (assuming gaussian)
    const auto progress = 100 * static_cast<float>(numberOfEventProcessed) / numberOfEventToBeProcessed;
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto precisionOfG4cout = G4cout.precision(2); // P.S. The precision of G4cout must be changed somewhere in G4, however inexplicably not changed back. We leave it as is.
    G4cout << std::put_time(std::localtime(&now), "%FT%T%z") << " > G4Event " << eventID << " finished in rank " << mpiEnv.CommWorldRank() << '\n'
           << "  ETA: " << eta << " +/- " << etaError << "  Progress of the rank: " << numberOfEventProcessed << '/' << numberOfEventToBeProcessed << " (" << std::fixed << progress << std::defaultfloat << "%)" << G4endl;
    G4cout.precision(precisionOfG4cout);
}

void MPIRunManager::RunEndReport(const G4int runID) const {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (mpiEnv.AtCommWorldWorker() or mpiEnv.GetVerboseLevel() < Env::VerboseLevel::Error) { return; }
    const auto wallTimeDHMS = FormatSecondToDHMS(fRunWallTime);
    const auto beginTime = std::chrono::system_clock::to_time_t(fRunBeginSystemTime);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto precisionOfG4cout = G4cout.precision(2); // P.S. The precision of G4cout must be changed somewhere in G4, however inexplicably not changed back. We leave it as is.
    G4cout << "-------------------------------> Run Finished <-------------------------------\n"
           << std::put_time(std::localtime(&now), "%FT%T%z") << " > Run " << runID << " finished on " << mpiEnv.CommWorldSize() << " ranks\n"
           << "  Start time: " << std::put_time(std::localtime(&beginTime), "%FT%T%z") << '\n'
           << "   Wall time: " << std::fixed << fRunWallTime << std::defaultfloat << " seconds";
    if (fRunWallTime > 60) { G4cout << " (" << wallTimeDHMS << ')'; }
    G4cout << "\n"
              "-------------------------------> Run Finished <-------------------------------"
           << G4endl;
    G4cout.precision(precisionOfG4cout);
}

void MPIRunManager::RunBeginReport(const G4int runID) {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (mpiEnv.AtCommWorldWorker() or mpiEnv.GetVerboseLevel() < Env::VerboseLevel::Error) { return; }
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    G4cout << "--------------------------------> Run Starts <--------------------------------\n"
           << std::put_time(std::localtime(&now), "%FT%T%z") << " > Run " << runID << " starts on " << mpiEnv.CommWorldSize() << " ranks\n"
           << "--------------------------------> Run Starts <--------------------------------" << G4endl;
}

std::string MPIRunManager::FormatSecondToDHMS(const double secondsInTotal) {
    const auto totalSeconds = std::llround(secondsInTotal);
    const auto div86400 = std::div(totalSeconds, 86400ll);
    const auto div3600 = std::div(div86400.rem, 3600ll);
    const auto div60 = std::div(div3600.rem, 60ll);
    const auto& [day, hour, minute, second] = std::tie(div86400.quot, div3600.quot, div60.quot, div60.rem);
    const auto addDay = day > 0;
    const auto addHour = addDay or hour > 0;
    const auto addMinute = addDay or addHour or minute > 0;

    std::array<char, std::numeric_limits<decltype(totalSeconds)>::digits10 + 3> buffer;
    std::string dhms;
    if (addDay) {
        const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), day).ptr;
        dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("d ");
    }
    if (addHour) {
        const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), hour).ptr;
        dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("h ");
    }
    if (addMinute) {
        const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), minute).ptr;
        dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("m ");
    }
    const auto* const charsEnd = std::to_chars(buffer.begin(), buffer.end(), second).ptr;
    dhms.append(std::string_view(buffer.cbegin(), charsEnd)).append("s");
    return dhms;
}

} // namespace MACE::inline Extension::Geant4X
