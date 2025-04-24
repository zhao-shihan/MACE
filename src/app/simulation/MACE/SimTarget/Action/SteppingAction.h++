#pragma once

#include "MACE/SimTarget/Messenger/ActionMessenger.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4ParticleDefinition.hh"
#include "G4UserSteppingAction.hh"

namespace MACE::SimTarget::inline Action {

class SteppingAction final : public Mustard::Env::Memory::PassiveSingleton<SteppingAction>,
                             public G4UserSteppingAction {
public:
    SteppingAction();

    auto KillIrrelevance(G4bool val) -> void { fKillIrrelevance = val; }

    auto UserSteppingAction(const G4Step* step) -> void override;

private:
    const G4ParticleDefinition* const fMuonPlus;
    const G4ParticleDefinition* const fMuonium;
    const G4ParticleDefinition* const fAntimuonium;
    G4bool fKillIrrelevance;

    ActionMessenger::Register<SteppingAction> fMessengerRegister;
};

} // namespace MACE::SimTarget::inline Action
