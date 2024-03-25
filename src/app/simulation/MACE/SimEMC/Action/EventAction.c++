#include "MACE/SimEMC/Action/EventAction.h++"
#include "MACE/SimEMC/Action/TrackingAction.h++"
#include "MACE/SimEMC/Analysis.h++"

#include "G4Event.hh"

namespace MACE::SimEMC::inline Action {

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

} // namespace MACE::SimEMC::inline Action
