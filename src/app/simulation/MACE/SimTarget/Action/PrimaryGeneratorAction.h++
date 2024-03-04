#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimTarget::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto PrimariesForEachG4Event(G4int n) -> void { fPrimariesForEachG4Event = n; }
    auto PrimariesForEachG4Event() const -> const auto& { return fPrimariesForEachG4Event; }

    auto GeneratePrimaries(G4Event* event) -> void override;

private:
    G4GeneralParticleSource fSurfaceMuonGenerator;

    G4int fPrimariesForEachG4Event;

    PrimaryGeneratorActionMessenger::Register<PrimaryGeneratorAction> fMessengerRegister;
};

} // namespace MACE::SimTarget::inline Action
