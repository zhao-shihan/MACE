#include "MACE/SimMACE/Action/EventAction.h++"
#include "MACE/SimMACE/Action/TrackingAction.h++"
#include "MACE/SimMACE/Analysis.h++"

#include "G4Event.hh"

namespace MACE::SimMACE::inline Action {

auto EventAction::BeginOfEventAction(const G4Event*) -> void {
    TrackingAction::Instance().ClearDecayVertexData();
}

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    auto& analysis{Analysis::Instance()};
    analysis.SubmitDecayVertexData(TrackingAction::Instance().DecayVertexData());
    analysis.EventEnd();
}

} // namespace MACE::SimMACE::inline Action
