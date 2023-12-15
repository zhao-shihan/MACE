#include "MACE/Compatibility/std2b/constexpr_cmath.h++"
#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/MPIRunManager.h++"
#include "MACE/Extension/Geant4X/MPIRunMessenger.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.h++"
#include "MACE/Utility/MPIUtil/MPIReseedPRNG.h++"

#include "G4ApplicationState.hh"
#include "G4Exception.hh"
#include "G4Run.hh"
#include "G4StateManager.hh"
#include "Randomize.hh"

#include "fmt/chrono.h"
#include "fmt/format.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <streambuf>
#include <string>
#include <string_view>

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
    fPrintProgressModulo{Env::MPIEnv::Instance().Sequential() ? 1 : Env::MPIEnv::Instance().CommWorldSize() + 1},
    fRunPlanOfThisRank{},
    fEventWallTimeStopwatch{},
    fEventWallTimeStatistic{},
    fRunBeginSystemTime{},
    fRunWallTimeStopwatch{},
    fRunCPUTimeStopwatch{},
    fRunBeginBarrierRequest{},
    fRunEndBarrierRequest{} {
    SetVerboseLevel(std2b::to_underlying(Env::MPIEnv::Instance().GetVerboseLevel()));
    MPIRunMessenger::Instance().AssignTo(this);
}

auto MPIRunManager::BeamOn(G4int nEvent, gsl::czstring macroFile, G4int nSelect) -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};

    MPIUtil::MPIReseedPRNG(*G4Random::getTheEngine());
    fRunPlanOfThisRank = MPIUtil::AllocMPIJobsJobWise(0, nEvent, mpiEnv.CommWorldSize(), mpiEnv.CommWorldRank());

    fakeRun = nEvent <= 0;
    numberOfEventToBeProcessed = nEvent;
    numberOfEventProcessed = 0;
    if (ConfirmBeamOnCondition()) {
        ConstructScoringWorlds();
        RunInitialization();
        DoEventLoop(fRunPlanOfThisRank.count, macroFile,
                    nSelect <= 0 ? nSelect : MPIUtil::AllocMPIJobsJobWise(0, nSelect, mpiEnv.CommWorldSize(), mpiEnv.CommWorldRank()).count);
        RunTermination();
    }
    fakeRun = false;
}

auto MPIRunManager::ConfirmBeamOnCondition() -> G4bool {
    const auto& mpiEnv{Env::MPIEnv::Instance()};

    if (const auto currentState{G4StateManager::GetStateManager()->GetCurrentState()};
        currentState != G4State_PreInit and currentState != G4State_Idle) {
        if (mpiEnv.AtCommWorldMaster()) {
            G4cerr << "Illegal application state - BeamOn ignored." << G4endl;
        }
        return false;
    }

    if (not initializedAtLeastOnce) {
        if (mpiEnv.AtCommWorldMaster()) {
            G4cerr << "Geant4 kernel should be initialized before the first BeamOn - BeamOn ignored." << G4endl;
        }
        return false;
    }

    if (numberOfEventToBeProcessed < mpiEnv.CommWorldSize()) {
        if (mpiEnv.AtCommWorldMaster()) {
            G4cerr << "The number of G4Event must >= the number of MPI ranks - BeamOn ignored." << G4endl;
        }
        return false;
    }

    MPI_Ibarrier(MPI_COMM_WORLD,
                 &fRunBeginBarrierRequest);
    MPI_Ibarrier(MPI_COMM_WORLD,
                 &fRunEndBarrierRequest);

    if (not geometryInitialized or not physicsInitialized) {
        if (verboseLevel > 0 and mpiEnv.AtCommWorldMaster()) {
            G4cout << "Start re-initialization because \n";
            if (not geometryInitialized) { G4cout << "  Geometry\n"; }
            if (not physicsInitialized) { G4cout << "  Physics processes\n"; }
            G4cout << "has been modified since last Run." << G4endl;
        }
        Initialize();
    }
    return true;
}

auto MPIRunManager::RunInitialization() -> void {
    // initialize run
    G4RunManager::RunInitialization();
    // wait for everyone to start
    MPI_Status runBeginBarrierStatus;
    MPI_Wait(&fRunBeginBarrierRequest,
             &runBeginBarrierStatus);
    // start the run stopwatch
    fRunBeginSystemTime = scsc::now();
    fRunWallTimeStopwatch = {};
    fRunCPUTimeStopwatch = {};
    // report
    if (fPrintProgressModulo >= 0) {
        if (const auto& mpiEnv{Env::MPIEnv::Instance()};
            mpiEnv.AtCommWorldMaster() and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
            RunBeginReport(runIDCounter);
        }
    }
}

auto MPIRunManager::InitializeEventLoop(G4int nEvent, gsl::czstring macroFile, G4int nSelect) -> void {
    // initialize event loop
    G4RunManager::InitializeEventLoop(nEvent, macroFile, nSelect);
    // reset event time statistic
    fEventWallTimeStatistic = {};
    // restart the event stopwatch just before the first event begins
    fEventWallTimeStopwatch = {};
}

auto MPIRunManager::ProcessOneEvent(G4int iEvent) -> void {
    G4RunManager::ProcessOneEvent(fRunPlanOfThisRank.begin + iEvent * fRunPlanOfThisRank.step);
}

auto MPIRunManager::TerminateOneEvent() -> void {
    // the terminating event ID
    const auto terminatedEventID{currentEvent->GetEventID()};
    // terminate the event
    G4RunManager::TerminateOneEvent();
    // read & restart the event stopwatch
    fEventWallTimeStatistic.Fill(fEventWallTimeStopwatch.SecondsElapsed());
    fEventWallTimeStopwatch = {};
    // report
    if (fPrintProgressModulo > 0 and terminatedEventID % fPrintProgressModulo == 0) {
        if (Env::MPIEnv::Instance().GetVerboseLevel() >= Env::VL::Error) {
            EventEndReport(terminatedEventID);
        }
    }
}

auto MPIRunManager::RunTermination() -> void {
    // terminate the run
    const auto endedRun{runIDCounter};
    G4RunManager::RunTermination();
    // stop the run stopwatch
    const auto cpuTime{fRunCPUTimeStopwatch.SecondsUsed()};
    const auto wallTime{fRunWallTimeStopwatch.SecondsElapsed()};
    // if running in parallel, per rank run end report
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (fPrintProgressModulo >= 0 and mpiEnv.GetVerboseLevel() >= Env::VL::Error and mpiEnv.Parallel()) {
        PerRankRunEndReport(endedRun, wallTime, cpuTime);
    }
    // wait for everyone to end
    MPI_Status runEndBarrierStatus;
    MPI_Wait(&fRunEndBarrierRequest,
             &runEndBarrierStatus);
    // run end report
    if (fPrintProgressModulo >= 0 and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
        std::array<MPI_Request, 2> fTimeMPIRequests;
        auto& [findMaxWallTime, sumCPUTime]{fTimeMPIRequests};
        double maxWallTime{};
        MPI_Ireduce(&wallTime,
                    &maxWallTime,
                    1,
                    MPI_DOUBLE,
                    MPI_MAX,
                    0,
                    MPI_COMM_WORLD,
                    &findMaxWallTime);
        double totalCPUTime{};
        MPI_Ireduce(&cpuTime,
                    &totalCPUTime,
                    1,
                    MPI_DOUBLE,
                    MPI_SUM,
                    0,
                    MPI_COMM_WORLD,
                    &sumCPUTime);
        std::array<MPI_Status, fTimeMPIRequests.size()> fTimeMPIStatuses;
        MPI_Waitall(fTimeMPIRequests.size(),
                    fTimeMPIRequests.data(),
                    fTimeMPIStatuses.data());
        if (mpiEnv.AtCommWorldMaster()) {
            RunEndReport(endedRun, fRunBeginSystemTime, maxWallTime, totalCPUTime);
        }
    }
}

auto MPIRunManager::EventEndReport(G4int eventID) const -> void {
    using namespace std::string_literals;
    const auto nEventRemain{fRunPlanOfThisRank.count - numberOfEventProcessed};
    const auto eta{SToDHMS(nEventRemain * fEventWallTimeStatistic.Mean())};
    const auto etaError{numberOfEventProcessed < 5 ?
                            "N/A"s :
                            SToDHMS(3 * nEventRemain * std::sqrt(fEventWallTimeStatistic.Variance() / numberOfEventProcessed))};
    const auto progress{static_cast<double>(numberOfEventProcessed) / fRunPlanOfThisRank.count};
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("Rank{}> {:%FT%T%z} > G4Event {} ended\n"
               "Rank{}>   Est. rem. time: {} +/- {}  Rank progress: {}/{} ({:.4}%)\n",
               mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), eventID,
               mpiEnv.CommWorldRank(), eta, etaError, numberOfEventProcessed, fRunPlanOfThisRank.count, 100 * progress);
}

auto MPIRunManager::RunBeginReport(G4int runID) -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("--------------------------------> G4Run starts <-------------------------------\n"
               "{:%FT%T%z} > G4Run {} starts on {} ranks\n"
               "--------------------------------> G4Run starts <-------------------------------\n",
               fmt::localtime(scsc::to_time_t(scsc::now())), runID, mpiEnv.CommWorldSize());
}

auto MPIRunManager::PerRankRunEndReport(G4int runID, double wallTime, double cpuTime) -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("Rank{}> {:%FT%T%z} > G4Run {} ended on rank {}, waiting for others...\n"
               "Rank{}>   Wall time: {:.3f} seconds{}\n"
               "Rank{}>    CPU time: {:.3f} seconds{}\n",
               mpiEnv.CommWorldRank(), fmt::localtime(scsc::to_time_t(scsc::now())), runID, mpiEnv.CommWorldRank(),
               mpiEnv.CommWorldRank(), wallTime, wallTime <= 60 ? "" : " (" + SToDHMS(wallTime) + ')',
               mpiEnv.CommWorldRank(), cpuTime, cpuTime <= 60 ? "" : " (" + SToDHMS(cpuTime) + ')');
}

auto MPIRunManager::RunEndReport(G4int runID, scsc::time_point runBeginTime, double maxWallTime, double totalCPUTime) -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    fmt::print("--------------------------------> G4Run ended <--------------------------------\n"
               "{:%FT%T%z} > G4Run {} ended on {} ranks\n"
               "  Start time: {:%FT%T%z}\n"
               "   Wall time: {:.3f} seconds{}\n"
               "    CPU time: {:.3f} seconds{}\n"
               "--------------------------------> G4Run ended <--------------------------------\n",
               fmt::localtime(scsc::to_time_t(scsc::now())), runID, mpiEnv.CommWorldSize(),
               fmt::localtime(scsc::to_time_t(runBeginTime)),
               maxWallTime, maxWallTime <= 60 ? "" : " (" + SToDHMS(maxWallTime) + ')',
               totalCPUTime, totalCPUTime <= 60 ? "" : " (" + SToDHMS(totalCPUTime) + ')');
}

auto MPIRunManager::SToDHMS(double secondsInTotal) -> std::string {
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

} // namespace MACE::inline Extension::Geant4X
