#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/MPIRunManager.h++"
#include "MACE/Extension/Geant4X/MPIRunMessenger.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.h++"
#include "MACE/Utility/MPIUtil/MPIReseedPRNG.h++"

#include "G4Exception.hh"
#include "G4Run.hh"
#include "Randomize.hh"

#include "mpi.h"

#include "fmt/chrono.h"
#include "fmt/format.h"

#include <algorithm>
#include <cstdlib>
#include <streambuf>
#include <string>

namespace MACE::inline Extension::Geant4X {

namespace internal {

FlipG4cout::FlipG4cout() {
    if (const auto& mpiEnv{Env::MPIEnv::Instance()};
        mpiEnv.AtCommWorldWorker() or
        mpiEnv.GetVerboseLevel() == Env::VL::Quiet) {
        static std::streambuf* gG4coutBufExchanger{nullptr};
        gG4coutBufExchanger = G4cout.rdbuf(gG4coutBufExchanger);
    }
}

} // namespace internal

MPIRunManager::MPIRunManager() :
    NonMoveableBase{},
    internal::PreG4RunManagerInitFlipG4cout{},
    G4RunManager{},
    internal::PostG4RunManagerInitFlipG4cout{},
    fNEventToBeMPIProcessed{},
    fEventIDRange{},
    fPrintProgressModulo{Env::MPIEnv::Instance().Sequential() ? 1 : Env::MPIEnv::Instance().CommWorldSize() + 1},
    fEventWallTimeStopwatch{},
    fEventWallTimeStatistic{},
    fRunCPUTimeStopwatch{},
    fRunCPUTime{},
    fRunWallTimeStopwatch{},
    fRunWallTime{},
    fRunBeginSystemTime{},
    fRunEndSystemTime{} {
    SetVerboseLevel(std2b::to_underlying(Env::MPIEnv::Instance().GetVerboseLevel()));
    MPIRunMessenger::Instance().AssignTo(this);
}

auto MPIRunManager::BeamOn(G4int nEvent, gsl::czstring macroFile, G4int nSelect) -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (nEvent < mpiEnv.CommWorldSize()) {
        if (mpiEnv.AtCommWorldMaster()) {
            G4Exception("MACE::Geant4X::MPIRunManager::CheckNEventIsAtLeastCommSize(...)",
                        "TooFewNEventOrTooMuchRank",
                        JustWarning,
                        "The number of G4Event must be greater or equal to the number of MPI ranks,\n"
                        "otherwise deadlock could raise in execution code.");
        }
        return;
    }

    MPIUtil::MPIReseedPRNG(*G4Random::getTheEngine());
    fNEventToBeMPIProcessed = nEvent;
    fEventIDRange = MPIUtil::AllocMPIJobsJobWise(0, nEvent, mpiEnv.CommWorldSize(), mpiEnv.CommWorldRank());
    G4RunManager::BeamOn(fEventIDRange.count, macroFile, nSelect);
}

auto MPIRunManager::RunInitialization() -> void {
    // initialize run
    G4RunManager::RunInitialization();
    // wait for everyone to start
    MPI_Barrier(MPI_COMM_WORLD);
    // start the run stopwatch
    fRunBeginSystemTime = std::chrono::system_clock::now();
    fRunCPUTimeStopwatch.Reset();
    fRunWallTimeStopwatch.Reset();
    // report
    if (fPrintProgressModulo >= 0) {
        RunBeginReport(runIDCounter);
    }
}

auto MPIRunManager::InitializeEventLoop(G4int nEvent, gsl::czstring macroFile, G4int nSelect) -> void {
    // initialize event loop
    G4RunManager::InitializeEventLoop(nEvent, macroFile, nSelect);
    // reset event time statistic
    fEventWallTimeStatistic = {};
    // restart the event stopwatch just before the first event begins
    fEventWallTimeStopwatch.Reset();
}

auto MPIRunManager::ProcessOneEvent(G4int iEvent) -> void {
    G4RunManager::ProcessOneEvent(fEventIDRange.begin + iEvent * fEventIDRange.step);
}

auto MPIRunManager::TerminateOneEvent() -> void {
    // the terminating event ID
    const auto terminatedEventID{currentEvent->GetEventID()};
    // terminate the event
    G4RunManager::TerminateOneEvent();
    // read & restart the event stopwatch
    fEventWallTimeStatistic.Fill(fEventWallTimeStopwatch.SecondsElapsed());
    fEventWallTimeStopwatch.Reset();
    // report
    if (fPrintProgressModulo > 0 and terminatedEventID % fPrintProgressModulo == 0) {
        EventEndReport(terminatedEventID);
    }
}

auto MPIRunManager::RunTermination() -> void {
    // terminate the run
    const auto endedRun{runIDCounter};
    G4RunManager::RunTermination();
    // stop the run stopwatch
    fRunWallTime = fRunWallTimeStopwatch.SecondsElapsed();
    fRunCPUTime = fRunCPUTimeStopwatch.SecondsUsed();
    // wait for everyone to finish
    MPI_Barrier(MPI_COMM_WORLD);
    // run end report
    if (fPrintProgressModulo >= 0) {
        RunEndReport(endedRun);
    }
}

namespace {

auto SToDHMS(double secondsInTotal) -> std::string {
    const auto totalSeconds{std::llround(secondsInTotal)};
    const auto div86400{std2b::div(totalSeconds, 86400ll)};
    const auto div3600{std2b::div(div86400.rem, 3600ll)};
    const auto div60{std2b::div(div3600.rem, 60ll)};
    const auto& [day, hour, minute, second]{std::tie(div86400.quot, div3600.quot, div60.quot, div60.rem)};
    if (day > 0) { return fmt::format("{}d {}h", day, hour); }
    if (hour > 0) { return fmt::format("{}h {}m", hour, minute); }
    if (minute > 0) { return fmt::format("{}m {}s", minute, second); }
    return fmt::format("{}s", second);
}

} // namespace

auto MPIRunManager::EventEndReport(G4int eventID) const -> void {
    using namespace std::string_literals;
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (mpiEnv.GetVerboseLevel() < Env::VL::Error) { return; }
    const auto nEventRemain{numberOfEventToBeProcessed - numberOfEventProcessed};
    const auto eta{SToDHMS(nEventRemain * fEventWallTimeStatistic.Mean())};
    const auto etaError{numberOfEventProcessed < 5 ?
                            "N/A"s :
                            SToDHMS(3 * nEventRemain * std::sqrt(fEventWallTimeStatistic.Variance() / numberOfEventProcessed))};
    const auto progress{static_cast<double>(numberOfEventProcessed) / numberOfEventToBeProcessed};
    using scsc = std::chrono::system_clock;
    fmt::print("Rank{}> {:%FT%T%z} > G4Event {} finished \n"
               "  Est. rem. time: {} +/- {}  Rank progress: {}/{} ({:.4}%)\n",
               mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), eventID,
               eta, etaError, numberOfEventProcessed, numberOfEventToBeProcessed, 100 * progress);
}

auto MPIRunManager::RunEndReport(G4int runID) const -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (mpiEnv.AtCommWorldWorker() or mpiEnv.GetVerboseLevel() < Env::VL::Error) { return; }
    using scsc = std::chrono::system_clock;
    fmt::print("------------------------------> G4Run Finished <------------------------------\n"
               "{:%FT%T%z} > G4Run {} finished on {} ranks\n"
               "  Start time: {:%FT%T%z}\n"
               "   Wall time: {:.2f} seconds {}\n"
               "------------------------------> G4Run Finished <------------------------------\n",
               fmt::localtime(scsc::to_time_t(scsc::now())), runID, mpiEnv.CommWorldSize(),
               fmt::localtime(scsc::to_time_t(fRunBeginSystemTime)),
               fRunWallTime, fRunWallTime > 60 ? '(' + SToDHMS(fRunWallTime) + ')' : "");
}

auto MPIRunManager::RunBeginReport(G4int runID) -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (mpiEnv.AtCommWorldWorker() or mpiEnv.GetVerboseLevel() < Env::VL::Error) { return; }
    using scsc = std::chrono::system_clock;
    fmt::print("-------------------------------> G4Run Starts <-------------------------------\n"
               "{:%FT%T%z} > G4Run {} starts on {} ranks\n"
               "-------------------------------> G4Run Starts <-------------------------------\n",
               fmt::localtime(scsc::to_time_t(scsc::now())), runID, mpiEnv.CommWorldSize());
}

} // namespace MACE::inline Extension::Geant4X
