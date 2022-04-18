#include "MACE/Simulation/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Particle/Muonium.hxx"
#include "MACE/Simulation/SimTarget/Action/TrackingAction.hxx"

#include "G4Track.hh"

namespace MACE::Simulation::SimTarget::Action {

using namespace Physics::Particle;

TrackingAction::TrackingAction() :
    fMuonium(Muonium::Definition()),
    fAntiMuonium(AntiMuonium::Definition()),
    fAnalysis(std::addressof(Analysis::Instance())) {}

void TrackingAction::PostUserTrackingAction(const G4Track* track) {
    const auto* const particle = track->GetParticleDefinition();
    if (particle == fMuonium or particle == fAntiMuonium) {
        const auto& muoniumTrack = fAnalysis->NewMuoniumTrack();
        muoniumTrack->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        muoniumTrack->SetVertexPosition(track->GetVertexPosition());
        muoniumTrack->SetDecayTime(track->GetGlobalTime());
        muoniumTrack->SetDecayPosition(track->GetPosition());
    }
}

} // namespace MACE::Simulation::SimTarget::Action
