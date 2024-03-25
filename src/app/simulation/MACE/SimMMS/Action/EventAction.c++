#include "MACE/SimMMS/Action/EventAction.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"
#include "MACE/SimMMS/Data/Analysis.h++"

#include "G4Event.hh"

namespace MACE::SimMMS::inline Action {

auto EventAction::BeginOfEventAction(const G4Event*) -> void {
    TrackingAction::Instance().ClearDecayVertexData();
}

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    auto& analysis{Data::Analysis::Instance()};
    analysis.SubmitDecayVertexData(TrackingAction::Instance().DecayVertexData());
    analysis.EventEnd();
}

} // namespace MACE::SimMMS::inline Action
