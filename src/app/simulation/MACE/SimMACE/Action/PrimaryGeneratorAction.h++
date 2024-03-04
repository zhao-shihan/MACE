#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimMACE::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto PulseWidth(G4double val) -> void { fPulseWidth = val; }
    auto PrimariesForEachG4Event(G4int n) -> void { fPrimariesForEachG4Event = n; }

    auto GeneratePrimaries(G4Event* event) -> void override;

private:
    G4GeneralParticleSource fGeneralParticleSource;

    G4double fPulseWidth;
    G4int fPrimariesForEachG4Event;

    PrimaryGeneratorActionMessenger::Register<PrimaryGeneratorAction> fMessengerRegister;
};

} // namespace MACE::SimMACE::inline Action
