#pragma once

#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimTarget/Action/RunAction.hxx"
#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Action/TrackingAction.hxx"
#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimulationG4/MPIRunManager.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <memory>

namespace MACE::SimTarget {

using Utility::ObserverPtr;

class RunManager final : public SimulationG4::MPIRunManager {
public:
    static auto& Instance() { return *static_cast<RunManager*>(GetRunManager()); }

    RunManager();
    ~RunManager();

    auto& GetDetectorConstruction() const { return *static_cast<Action::DetectorConstruction*>(userDetector); }
    auto& GetPhysicsList() const { return *fPhysicsList; }
    auto& GetPrimaryGeneratorAction() const { return *static_cast<Action::PrimaryGeneratorAction*>(userPrimaryGeneratorAction); }
    auto& GetRunAction() const { return *static_cast<Action::RunAction*>(userRunAction); }
    auto& GetSteppingAction() const { return *static_cast<Action::SteppingAction*>(userSteppingAction); }
    auto& GetTrackingAction() const { return *static_cast<Action::TrackingAction*>(userTrackingAction); }
    auto& GetAnalysis() const { return *fAnalysis; }

private:
    ObserverPtr<Action::PhysicsList> fPhysicsList;
    std::unique_ptr<Analysis> fAnalysis;
};

} // namespace MACE::SimTarget
