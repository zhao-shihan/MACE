#pragma once

#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimTarget/Action/EventAction.hxx"
#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/Action/RunAction.hxx"
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
    auto& GetRunAction() const { return *static_cast<RunAction*>(userRunAction); }
    auto& GetPrimaryGeneratorAction() const { return *static_cast<PrimaryGeneratorAction*>(userPrimaryGeneratorAction); }
    auto& GetEventAction() const { return *static_cast<EventAction*>(userEventAction); }
    // auto& GetStackingAction()         const { return *static_cast<*>(userStackingAction); }
    // auto& GetTrackingAction()         const { return *static_cast<*>(userTrackingAction); }
    // auto& GetSteppingAction()         const { return *static_cast<*>(userSteppingAction); }
};

} // namespace MACE::Simulation::SimTarget
