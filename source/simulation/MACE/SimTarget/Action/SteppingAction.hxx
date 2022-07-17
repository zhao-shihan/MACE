#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4ParticleDefinition.hh"
#include "G4UserSteppingAction.hh"

namespace MACE::SimTarget::Action {

using Utility::ObserverPtr;

class SteppingAction final : public G4UserSteppingAction {
public:
    SteppingAction();
    ~SteppingAction() noexcept = default;
    SteppingAction(const SteppingAction&) = delete;
    SteppingAction& operator=(const SteppingAction&) = delete;

    void SetKillIrrelevants(G4bool val) { fKillIrrelevants = val; }

    void UserSteppingAction(const G4Step* step) override;

private:
    const ObserverPtr<const G4ParticleDefinition> fMuonPlus;
    const ObserverPtr<const G4ParticleDefinition> fMuonium;
    const ObserverPtr<const G4ParticleDefinition> fAntiMuonium;
    G4bool fKillIrrelevants;
};

} // namespace MACE::SimTarget::Action
