#pragma once

#include "MACE/Simulation/SimTarget/Analysis.hxx"

#include "G4UserTrackingAction.hh"

namespace MACE::Simulation::SimTarget::Action {

class TrackingAction final : public G4UserTrackingAction {
public:
    TrackingAction();
    ~TrackingAction() noexcept = default;

    void PostUserTrackingAction(const G4Track*) override;

private:
    const ObserverPtr<const G4ParticleDefinition> fMuonium;
    const ObserverPtr<const G4ParticleDefinition> fAntiMuonium;
    const ObserverPtr<Analysis> fAnalysis;
};

} // namespace MACE::Simulation::SimTarget::Action
