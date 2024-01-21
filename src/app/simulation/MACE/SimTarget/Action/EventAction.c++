#include "MACE/SimTarget/Action/EventAction.h++"
#include "MACE/SimTarget/Action/TrackingAction.h++"

#include "G4Event.hh"

namespace MACE::SimTarget::inline Action {

auto EventAction::BeginOfEventAction(const G4Event* event) -> void {
    TrackingAction::Instance().EventID(event->GetEventID());
}

} // namespace MACE::SimTarget::inline Action
