#pragma once

#include "MACE/Env/Memory/PassiveSingleton.hxx"

#include "G4ParticleDefinition.hh"
#include "G4UserSteppingAction.hh"

namespace MACE::SimTarget::inline Action {

class SteppingAction final : public Env::Memory::PassiveSingleton<SteppingAction>,
                             public G4UserSteppingAction {
public:
    SteppingAction();

    void SetKillIrrelevants(G4bool val) { fKillIrrelevants = val; }

    void UserSteppingAction(const G4Step* step) override;

private:
    const G4ParticleDefinition* const fMuonPlus;
    const G4ParticleDefinition* const fMuonium;
    const G4ParticleDefinition* const fAntimuonium;
    G4bool fKillIrrelevants;
};

} // namespace MACE::SimTarget::inline Action
