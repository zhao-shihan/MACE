#pragma once

#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"
#include "Mustard/Extension/Geant4X/Generator/FromDataPrimaryGenerator.h++"
#include "Mustard/Extension/Geant4X/Generator/GeneralParticleSourceX.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimTarget::inline Action {

class PrimaryGeneratorAction final : public Mustard::Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto SwitchToGPSX() -> void { fGenerator = &fAvailableGenerator.gpsx; }
    auto SwitchToFromDataPrimaryGenerator() -> void { fGenerator = &fAvailableGenerator.fromDataPrimaryGenerator; }

    auto NVertex() const -> int;

    auto GeneratePrimaries(G4Event* event) -> void override { fGenerator->GeneratePrimaryVertex(event); }

private:
    struct {
        Mustard::Geant4X::GeneralParticleSourceX gpsx;
        Mustard::Geant4X::FromDataPrimaryGenerator fromDataPrimaryGenerator;
    } fAvailableGenerator;
    G4VPrimaryGenerator* fGenerator;

    PrimaryGeneratorActionMessenger::Register<PrimaryGeneratorAction> fPrimaryGeneratorActionMessengerRegister;
};

} // namespace MACE::SimTarget::inline Action
