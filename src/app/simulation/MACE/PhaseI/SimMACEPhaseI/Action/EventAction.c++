#include "MACE/PhaseI/SimMACEPhaseI/Action/EventAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"

#include "G4Event.hh"

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

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

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
