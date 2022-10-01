#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Geant4X/MPIRunManager.hxx"
#include "MACE/Geant4X/MPIRunMessenger.hxx"
#include "MACE/Math/IntegerPower.hxx"
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
#include <iomanip>
#include <ios>
#include <string>

namespace MACE::Geant4X {

using namespace std::string_view_literals;

namespace internal {

FlipG4cout::FlipG4cout() {
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        mpiEnv.AtWorldWorker() or
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
    fEventIDRange{-1, -1, 0, 0},
    fEventIDCounter(-1),
    fPrintProgress(-1),
    fEventWallTimer(),
    fEventWallTime(0),
    fNAvgEventWallTime(0),
    fNDevEventWallTime(0),
    fRunCPUTimer(),
    fRunCPUTime(0),
    fRunWallTimer(),
    fRunWallTime(0),
    fRunBeginSystemTime(),
    fRunEndSystemTime() {
    MPIRunMessenger::Instance().AssignTo(this);
}

void MPIRunManager::SetPrintProgress(G4int val) {
    printModulo = -1;
    fPrintProgress = val;
}

void MPIRunManager::BeamOn(G4int nEvent, gsl::czstring macroFile, G4int nSelect) {
    if (CheckNEventIsAtLeastCommSize(nEvent)) {
        Utility::MPIUtil::MPIReSeedCLHEPRandom(G4Random::getTheEngine());
        fTotalNumberOfEventsToBeProcessed = nEvent;
        const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        fEventIDRange = Utility::MPIUtil::AllocMPIJobsJobWise(0, nEvent, mpiEnv.WorldCommSize(), mpiEnv.WorldCommRank());
        G4RunManager::BeamOn(fEventIDRange.count, macroFile, nSelect);
    }
}

void MPIRunManager::RunInitialization() {
    // wait for everyone to start
    MACE_CHECKED_MPI_CALL(MPI_Barrier,
                          MPI_COMM_WORLD)
    // start the run timer
    fRunBeginSystemTime = std::chrono::system_clock::now();
    fRunCPUTimer.Reset();
    fRunWallTimer.Reset();
    // initialize run
    G4RunManager::RunInitialization();
    // report
    if (fPrintProgress >= 0) {
        RunBeginReport(runIDCounter);
    }
}

void MPIRunManager::InitializeEventLoop(G4int nEvent, gsl::czstring macroFile, G4int nSelect) {
    // reset event time statistic
    fNAvgEventWallTime = 0;
    fNDevEventWallTime = 0;
    // initialize event loop
    fEventIDCounter = fEventIDRange.begin;
    G4RunManager::InitializeEventLoop(nEvent, macroFile, nSelect);
    // restart the event timer just before the first event begins
    fEventWallTimer.Reset();
}

void MPIRunManager::TerminateOneEvent() {
    // terminate the event
    G4RunManager::TerminateOneEvent();
    const auto endedEvent = fEventIDCounter;
    fEventIDCounter += fEventIDRange.step;
    // read & restart the event timer
    fEventWallTime = fEventWallTimer.SecondsElapsed();
    fEventWallTimer.Reset();
    fNAvgEventWallTime += fEventWallTime;
    fNDevEventWallTime += Math::Pow2(fEventWallTime - fNAvgEventWallTime / numberOfEventProcessed);
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
    fRunWallTime = fRunWallTimer.SecondsElapsed();
    fRunCPUTime = fRunCPUTimer.SecondsUsed();
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
        nEvent < mpiEnv.WorldCommSize()) {
        if (mpiEnv.AtWorldMaster()) {
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
    const auto etaError = numberOfEventProcessed < 5 ?
                              std::string("N/A"sv) :
                              FormatSecondToDHMS(std::lround(1.96 * std::sqrt(fNDevEventWallTime / (numberOfEventProcessed - 1)) * nEventRemain)); // 95% C.L. (assuming gaussian)
    const auto progress = 100 * static_cast<float>(numberOfEventProcessed) / numberOfEventToBeProcessed;
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto precisionOfG4cout = G4cout.precision(2); // P.S. The precision of G4cout must be changed somewhere in G4, however inexplicably not changed back. We leave it as is.
    G4cout << std::put_time(std::localtime(&now), "%FT%T%z") << " > Event "sv << event << " finished in rank "sv << mpiEnv.WorldCommRank() << '\n'
           << "  ETA: "sv << eta << " +/- "sv << etaError << "  Progress of the rank: "sv << numberOfEventProcessed << '/' << numberOfEventToBeProcessed << " ("sv << std::fixed << progress << std::defaultfloat << "%)"sv << G4endl;
    G4cout.precision(precisionOfG4cout);
}

void MPIRunManager::RunEndReport(G4int run) const {
    const auto& mpiEnv = Environment::MPIEnvironment::Instance();
    if (mpiEnv.AtWorldWorker() or mpiEnv.GetVerboseLevel() < Environment::VerboseLevel::Error) { return; }
    const auto wallTimeDHMS = FormatSecondToDHMS(std::lround(fRunWallTime));
    const auto beginTime = std::chrono::system_clock::to_time_t(fRunBeginSystemTime);
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const auto precisionOfG4cout = G4cout.precision(2); // P.S. The precision of G4cout must be changed somewhere in G4, however inexplicably not changed back. We leave it as is.
    G4cout << "-------------------------------> Run Finished <-------------------------------\n"sv
           << std::put_time(std::localtime(&now), "%FT%T%z") << " > Run "sv << run << " finished on "sv << mpiEnv.WorldCommSize() << " ranks\n"sv
           << "  Start time: "sv << std::put_time(std::localtime(&beginTime), "%FT%T%z") << '\n'
           << "   Wall time: "sv << std::fixed << fRunWallTime << std::defaultfloat << " seconds"sv;
    if (fRunWallTime > 60) { G4cout << " ("sv << wallTimeDHMS << ')'; }
    G4cout << "\n"sv
              "-------------------------------> Run Finished <-------------------------------"sv
           << G4endl;
    G4cout.precision(precisionOfG4cout);
}

void MPIRunManager::RunBeginReport(G4int run) {
    const auto& mpiEnv = Environment::MPIEnvironment::Instance();
    if (mpiEnv.AtWorldWorker() or mpiEnv.GetVerboseLevel() < Environment::VerboseLevel::Error) { return; }
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    G4cout << "--------------------------------> Run Starts <--------------------------------\n"sv
           << std::put_time(std::localtime(&now), "%FT%T%z") << " > Run "sv << run << " starts on "sv << mpiEnv.WorldCommSize() << " ranks\n"sv
           << "--------------------------------> Run Starts <--------------------------------"sv << G4endl;
}

std::string MPIRunManager::FormatSecondToDHMS(long secondsInTotal) {
    const auto div86400 = std::div(secondsInTotal, 86400L);
    const auto div3600 = std::div(div86400.rem, 3600L);
    const auto div60 = std::div(div3600.rem, 60L);
    const auto& [day, hour, minute, second] = std::tie(div86400.quot, div3600.quot, div60.quot, div60.rem);
    const auto addDay = day > 0;
    const auto addHour = addDay or hour > 0;
    const auto addMinute = addDay or addHour or minute > 0;

    char buffer[std::numeric_limits<long>::digits10 + 3]; // long enough to store a "long"
    const auto bufferEnd = buffer + std::size(buffer);
    std::string dhms;
    if (addDay) {
        const auto charLast = std::to_chars(buffer, bufferEnd, day).ptr;
        dhms.append(std::string_view(buffer, charLast)).append("d "sv);
    }
    if (addHour) {
        const auto charLast = std::to_chars(buffer, bufferEnd, hour).ptr;
        dhms.append(std::string_view(buffer, charLast)).append("h "sv);
    }
    if (addMinute) {
        const auto charLast = std::to_chars(buffer, bufferEnd, minute).ptr;
        dhms.append(std::string_view(buffer, charLast)).append("m "sv);
    }
    const auto charLast = std::to_chars(buffer, bufferEnd, second).ptr;
    dhms.append(std::string_view(buffer, charLast)).append("s"sv);
    return dhms;
}

} // namespace MACE::Geant4X
