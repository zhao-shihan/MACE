#include "MACE/SimMMS/Action/EventAction.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"
#include "MACE/SimMMS/Analysis.h++"

#include "G4Event.hh"

namespace MACE::SimMMS::inline Action {

auto EventAction::BeginOfEventAction(const G4Event*) -> void {
    if (auto& trackingAction{TrackingAction::Instance()};
        trackingAction.SaveDecayVertexData()) {
        trackingAction.ClearDecayVertexData();
    }
}

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    auto& analysis{Analysis::Instance()};
    if (const auto& trackingAction{TrackingAction::Instance()};
        trackingAction.SaveDecayVertexData()) {
        analysis.SubmitDecayVertexData(trackingAction.DecayVertexData());
    }
    analysis.EventEnd();
}

} // namespace MACE::SimMMS::inline Action
