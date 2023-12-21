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
    fTask{} {
    SetVerboseLevel(std2b::to_underlying(Env::MPIEnv::Instance().GetVerboseLevel()));
    PrintProgressModulo(Env::MPIEnv::Instance().Parallel() ?
                            Env::MPIEnv::Instance().CommWorldSize() + 1 :
                            1);
    fTask.TaskName("G4Event");
    MPIRunMessenger::Instance().AssignTo(this);
}

auto MPIRunManager::BeamOn(G4int nEvent, gsl::czstring macroFile, G4int nSelect) -> void {
    MPIUtil::MPIReseedPRNG(*G4Random::getTheEngine());
    fakeRun = nEvent <= 0;
    if (ConfirmBeamOnCondition()) {
        fTask.AssignTask(nEvent);
        numberOfEventToBeProcessed = nEvent;
        numberOfEventProcessed = 0;
        ConstructScoringWorlds();
        RunInitialization();
        DoEventLoop(nEvent, macroFile, nSelect);
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

auto MPIRunManager::DoEventLoop(G4int nEvent, const char* macroFile, G4int nSelect) -> void {
    InitializeEventLoop(nEvent, macroFile, nSelect);
    // Set name for message
    fTask.RunName(fmt::format("G4Run {}", currentRun->GetRunID()));
    // Event loop
    for (auto i{fTask.Next()}; i.has_value(); i = fTask.Next()) {
        ProcessOneEvent(*i);
        TerminateOneEvent();
        if (runAborted) { break; }
    }
    // If multi-threading, TerminateEventLoop() is invoked after all threads are finished.
    // MPIRunManager::runManagerType is sequentialRM.
    if (runManagerType == sequentialRM) { TerminateEventLoop(); }
}

// auto MPIRunManager::RunTermination() -> void {
//     G4RunManager::RunTermination();
//     // run end report
//     if (const auto& mpiEnv{Env::MPIEnv::Instance()};
//         fPrintProgressModulo >= 0 and mpiEnv.GetVerboseLevel() >= Env::VL::Error) {
//         // // if running in parallel, per rank run end report
//         // if (mpiEnv.Parallel()) { PerRankRunEndReport(endedRun, wallTime, cpuTime); }
//         std::array<MPI_Request, 2> fTimeMPIRequests;
//         auto& [findMaxWallTime, sumCPUTime]{fTimeMPIRequests};
//         double maxWallTime{};
//         MPI_Ireduce(&wallTime,
//                     &maxWallTime,
//                     1,
//                     MPI_DOUBLE,
//                     MPI_MAX,
//                     0,
//                     MPI_COMM_WORLD,
//                     &findMaxWallTime);
//         double totalCPUTime{};
//         MPI_Ireduce(&cpuTime,
//                     &totalCPUTime,
//                     1,
//                     MPI_DOUBLE,
//                     MPI_SUM,
//                     0,
//                     MPI_COMM_WORLD,
//                     &sumCPUTime);
//         MPI_Waitall(fTimeMPIRequests.size(),
//                     fTimeMPIRequests.data(),
//                     MPI_STATUSES_IGNORE);
//         if (mpiEnv.AtCommWorldMaster()) {
//             RunEndReport(endedRun, fRunBeginSystemTime, maxWallTime, totalCPUTime);
//         }
//     } else {
//         MPI_Barrier(MPI_COMM_WORLD);
//     }
// }

} // namespace MACE::inline Extension::Geant4X
