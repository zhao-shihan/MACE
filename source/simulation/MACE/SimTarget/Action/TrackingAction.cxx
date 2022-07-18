#include "MACE/SimTarget/Action/TrackingAction.hxx"
#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/MuoniumTrack.hxx"
#include "MACE/Simulation/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Particle/Muonium.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4Track.hh"

namespace MACE::SimTarget::Action {

using namespace Simulation::Physics::Particle;
using namespace Utility::PhysicalConstant;

TrackingAction::TrackingAction() :
    fMuonium(Muonium::Definition()),
    fAntiMuonium(AntiMuonium::Definition()),
    fMuoniumTrack(nullptr) {}

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    const auto* const particle = track->GetParticleDefinition();
    if (particle == fMuonium or particle == fAntiMuonium) {
        fMuoniumTrack = Analysis::Instance().NewMuoniumTrack();
        fMuoniumTrack->SetVertexTime(track->GetGlobalTime());
        fMuoniumTrack->SetVertexPosition(track->GetPosition());
        fMuoniumTrack->SetVertexMomentum(track->GetMomentum());
    }
}

void TrackingAction::PostUserTrackingAction(const G4Track* track) {
    const auto* const particle = track->GetParticleDefinition();
    if (particle == fMuonium or particle == fAntiMuonium) {
        fMuoniumTrack->SetDecayTime(track->GetGlobalTime());
        fMuoniumTrack->SetDecayPosition(track->GetPosition());
        fMuoniumTrack->SetDecayMomentum(track->GetMomentum());
    }
}

} // namespace MACE::SimTarget::Action
