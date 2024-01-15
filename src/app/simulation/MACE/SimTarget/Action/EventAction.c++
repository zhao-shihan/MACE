#include "MACE/SimTarget/Action/EventAction.h++"
#include "MACE/SimTarget/Action/TrackingAction.h++"

#include "G4Event.hh"

namespace MACE::SimTarget::inline Action {

void EventAction::BeginOfEventAction(const G4Event* event) {
    TrackingAction::Instance().EventID(event->GetEventID());
}

} // namespace MACE::SimTarget::inline Action
