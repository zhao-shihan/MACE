#pragma once

#include "MACE/Environment/Memory/FreeSingleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4ParticleDefinition.hh"
#include "G4UserSteppingAction.hh"

namespace MACE::SimTarget::Action {

using Utility::ObserverPtr;

class SteppingAction final : public Environment::Memory::FreeSingleton<SteppingAction>,
                             public G4UserSteppingAction {
public:
    SteppingAction();

    void SetKillIrrelevants(G4bool val) { fKillIrrelevants = val; }

    void UserSteppingAction(const G4Step* step) override;

private:
    const ObserverPtr<const G4ParticleDefinition> fMuonPlus;
    const ObserverPtr<const G4ParticleDefinition> fMuonium;
    const ObserverPtr<const G4ParticleDefinition> fAntiMuonium;
    G4bool fKillIrrelevants;
};

} // namespace MACE::SimTarget::Action
