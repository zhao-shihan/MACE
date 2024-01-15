#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4ParticleDefinition.hh"
#include "G4UserSteppingAction.hh"

namespace MACE::SimTarget::inline Action {

class SteppingAction final : public Env::Memory::PassiveSingleton<SteppingAction>,
                             public G4UserSteppingAction {
public:
    SteppingAction();

    auto SetKillIrrelevants(G4bool val) -> void { fKillIrrelevants = val; }

    auto UserSteppingAction(const G4Step* step) -> void override;

private:
    const G4ParticleDefinition* const fMuonPlus;
    const G4ParticleDefinition* const fMuonium;
    const G4ParticleDefinition* const fAntimuonium;
    G4bool fKillIrrelevants;
};

} // namespace MACE::SimTarget::inline Action
