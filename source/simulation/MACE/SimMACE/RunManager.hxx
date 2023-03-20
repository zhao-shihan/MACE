#pragma once

#include "MACE/Extension/Geant4X/MPIRunManager.hxx"
#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Action/EventAction.hxx"
#include "MACE/SimMACE/Action/PhysicsList.hxx"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimMACE/Action/RunAction.hxx"
#include "MACE/SimMACE/Analysis.hxx"

#include <memory>

namespace MACE::SimMACE {

class RunManager final : public Geant4X::MPIRunManager {
public:
    static auto& Instance() { return static_cast<RunManager&>(*GetRunManager()); }

    RunManager();

    auto& GetDetectorConstruction() const { return static_cast<DetectorConstruction&>(*userDetector); }
    auto& GetEventAction() const { return static_cast<EventAction&>(*userEventAction); }
    auto& GetPhysicsList() const { return *fPhysicsList; }
    auto& GetPrimaryGeneratorAction() const { return static_cast<PrimaryGeneratorAction&>(*userPrimaryGeneratorAction); }
    auto& GetRunAction() const { return static_cast<RunAction&>(*userRunAction); }
    auto& GetAnalysis() const { return *fAnalysis; }

private:
    PhysicsList* const fPhysicsList;
    std::unique_ptr<Analysis> fAnalysis;
};

} // namespace MACE::SimMACE
