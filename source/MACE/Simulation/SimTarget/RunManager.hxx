#pragma once

#include "MACE/Simulation/SimTarget/DetectorConstruction.hxx"
#include "MACE/Simulation/SimTarget/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/RunAction.hxx"
#include "MACE/Simulation/SimTarget/TrackingAction.hxx"
#include "MACE/Utility/MPITool/G4MPIRunManager.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

namespace MACE::Simulation::SimTarget {

class RunManager final : public MACE::Utility::MPITool::G4MPIRunManager {
public:
    static auto& Instance() { return *static_cast<RunManager*>(GetRunManager()); }

    RunManager();
    ~RunManager() noexcept = default;
    RunManager(const RunManager&) = delete;
    RunManager& operator=(const RunManager&) = delete;

    auto& GetDetectorConstruction() const { return *static_cast<DetectorConstruction*>(userDetector); }
    auto& GetPhysicsList() const { return *physicsList; }
    auto& GetPrimaryGeneratorAction() const { return *static_cast<PrimaryGeneratorAction*>(userPrimaryGeneratorAction); }
    auto& GetRunAction() const { return *static_cast<RunAction*>(userRunAction); }
    auto& GetTrackingAction() const { return *static_cast<TrackingAction*>(userTrackingAction); }
};

} // namespace MACE::Simulation::SimTarget
