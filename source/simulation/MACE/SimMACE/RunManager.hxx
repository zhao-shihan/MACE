#pragma once

#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Action/EventAction.hxx"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimMACE/Action/RunAction.hxx"
#include "MACE/SimulationG4/MPIRunManager.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

namespace MACE::SimMACE {

using namespace MACE::SimMACE::Action;

class RunManager final : public SimulationG4::MPIRunManager {
public:
    static auto& Instance() { return *static_cast<RunManager*>(GetRunManager()); }

    RunManager();
    ~RunManager() noexcept = default;
    RunManager(const RunManager&) = delete;
    RunManager& operator=(const RunManager&) = delete;

    auto& GetDetectorConstruction() const { return *static_cast<DetectorConstruction*>(userDetector); }
    auto& GetEventAction() const { return *static_cast<EventAction*>(userEventAction); }
    auto& GetPhysicsList() const { return *physicsList; }
    auto& GetPrimaryGeneratorAction() const { return *static_cast<PrimaryGeneratorAction*>(userPrimaryGeneratorAction); }
    auto& GetRunAction() const { return *static_cast<RunAction*>(userRunAction); }
    // auto& GetStackingAction()         const { return *static_cast<*>(userStackingAction); }
    // auto& GetTrackingAction()         const { return *static_cast<*>(userTrackingAction); }
    // auto& GetSteppingAction()         const { return *static_cast<*>(userSteppingAction); }
};

} // namespace MACE::SimMACE
