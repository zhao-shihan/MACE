#include "MACE/SimVeto/Action/EventAction.h++"
// #include "MACE/SimVeto/Action/TrackingAction.h++"
#include "MACE/SimVeto/Analysis.h++"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"

#include "G4Event.hh"

namespace MACE::SimVeto::inline Action {

auto EventAction::BeginOfEventAction(const G4Event*) -> void {
    // if (auto& trackingAction{TrackingAction::Instance()};
    //     trackingAction.SaveDecayVertexData()) {
    //     trackingAction.ClearDecayVertexData();
    // }
}

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    auto& analysis{Analysis::Instance()};
    // if (const auto& trackingAction{TrackingAction::Instance()};
    //     trackingAction.SaveDecayVertexData()) {
    //     analysis.SubmitDecayVertexData(trackingAction.DecayVertexData());
    // }
    analysis.EventEnd();
}

} // namespace MACE::SimVeto::inline Action
