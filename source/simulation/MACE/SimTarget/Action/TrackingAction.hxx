#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UserTrackingAction.hh"

class G4ParticleDefinition;

namespace MACE::SimTarget {

class MuoniumTrack;

namespace Action {

using Utility::ObserverPtr;

class TrackingAction final : public G4UserTrackingAction {
public:
    TrackingAction();
    ~TrackingAction() = default;
    TrackingAction(const TrackingAction&) = delete;
    TrackingAction& operator=(const TrackingAction&) = delete;

    void PreUserTrackingAction(const G4Track* track) override;
    void PostUserTrackingAction(const G4Track* track) override;

private:
    const ObserverPtr<const G4ParticleDefinition> fMuonium;
    const ObserverPtr<const G4ParticleDefinition> fAntiMuonium;
    ObserverPtr<MuoniumTrack> fMuoniumTrack;
};

} // namespace Action

} // namespace MACE::SimTarget
