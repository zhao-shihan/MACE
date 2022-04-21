#pragma once

#include "MACE/Simulation/SimTarget/Analysis.hxx"

#include "G4UserTrackingAction.hh"

namespace MACE::Simulation::SimTarget::Action {

class TrackingAction final : public G4UserTrackingAction {
public:
    TrackingAction();
    ~TrackingAction() noexcept = default;
    TrackingAction(const TrackingAction&) = delete;
    TrackingAction& operator=(const TrackingAction&) = delete;

    void PreUserTrackingAction(const G4Track* track) override;
    void PostUserTrackingAction(const G4Track* track) override;

private:
    const ObserverPtr<const G4ParticleDefinition> fMuonium;
    const ObserverPtr<const G4ParticleDefinition> fAntiMuonium;
    const ObserverPtr<Analysis> fAnalysis;
    ObserverPtr<MuoniumTrack> fMuoniumTrack;
};

} // namespace MACE::Simulation::SimTarget::Action
