#pragma once

#include "MACE/Simulation/SimTarget/Analysis.hxx"

#include "G4UserTrackingAction.hh"

namespace MACE::Simulation::SimTarget::Action {

class TrackingAction final : public G4UserTrackingAction {
public:
    TrackingAction();
    ~TrackingAction() noexcept;

    void PostUserTrackingAction(const G4Track*) override;

private:
    ObserverPtr<Analysis> fAnalysis;
};

} // namespace MACE::Simulation::SimTarget
