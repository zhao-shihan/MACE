#include "MACE/Simulation/SimTarget/Action/EventAction.h++"
#include "MACE/Simulation/SimTarget/Action/TrackingAction.h++"

#include "G4Event.hh"

namespace MACE::inline Simulation::SimTarget::inline Action {

void EventAction::BeginOfEventAction(const G4Event* event) {
    TrackingAction::Instance().EventID(event->GetEventID());
}

} // namespace MACE::inline Simulation::SimTarget::inline Action
