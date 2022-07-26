#pragma once

#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Action/EventAction.hxx"
#include "MACE/SimMACE/Action/PhysicsList.hxx"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimMACE/Action/RunAction.hxx"
#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimulationG4/MPIRunManager.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include <memory>

namespace MACE::SimMACE {

using Utility::ObserverPtr;

class RunManager final : public SimulationG4::MPIRunManager {
public:
    static auto& Instance() { return static_cast<RunManager&>(*GetRunManager()); }

    RunManager();

    auto& GetDetectorConstruction() const { return static_cast<Action::DetectorConstruction&>(*userDetector); }
    auto& GetEventAction() const { return static_cast<Action::EventAction&>(*userEventAction); }
    auto& GetPhysicsList() const { return *fPhysicsList; }
    auto& GetPrimaryGeneratorAction() const { return static_cast<Action::PrimaryGeneratorAction&>(*userPrimaryGeneratorAction); }
    auto& GetRunAction() const { return static_cast<Action::RunAction&>(*userRunAction); }
    auto& GetAnalysis() const { return *fAnalysis; }

private:
    ObserverPtr<Action::PhysicsList> fPhysicsList;
    std::unique_ptr<Analysis> fAnalysis;
};

} // namespace MACE::SimMACE
