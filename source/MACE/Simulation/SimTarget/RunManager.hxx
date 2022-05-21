#pragma once

#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/Action/RunAction.hxx"
#include "MACE/Simulation/SimTarget/Action/SteppingAction.hxx"
#include "MACE/Simulation/SimTarget/Action/TrackingAction.hxx"
#include "MACE/Simulation/Utility/MPIRunManager.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

namespace MACE::Simulation::SimTarget {

using namespace Action;

class RunManager final : public Simulation::Utility::MPIRunManager {
public:
    static auto& Instance() { return *static_cast<RunManager*>(GetRunManager()); }

    RunManager();
    ~RunManager() noexcept;
    RunManager(const RunManager&) = delete;
    RunManager& operator=(const RunManager&) = delete;

    auto& GetDetectorConstruction() const { return *static_cast<DetectorConstruction*>(userDetector); }
    auto& GetPhysicsList() const { return *physicsList; }
    auto& GetPrimaryGeneratorAction() const { return *static_cast<PrimaryGeneratorAction*>(userPrimaryGeneratorAction); }
    auto& GetRunAction() const { return *static_cast<RunAction*>(userRunAction); }
    auto& GetSteppingAction() const { return *static_cast<SteppingAction*>(userSteppingAction); }
    auto& GetTrackingAction() const { return *static_cast<TrackingAction*>(userTrackingAction); }
};

} // namespace MACE::Simulation::SimTarget
