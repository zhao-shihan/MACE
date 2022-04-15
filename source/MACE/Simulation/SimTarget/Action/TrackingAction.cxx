#include "MACE/Simulation/SimTarget/Action/TrackingAction.hxx"

#include "G4Track.hh"

namespace MACE::Simulation::SimTarget::Action {

TrackingAction::TrackingAction() :
    fAnalysis(std::addressof(Analysis::Instance())) {}

void TrackingAction::PostUserTrackingAction(const G4Track* track) {
}

} // namespace MACE::Simulation::SimTarget::Action
