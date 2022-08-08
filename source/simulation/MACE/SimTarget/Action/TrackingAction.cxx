#include "MACE/Geant4X/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/SimTarget/Action/TrackingAction.hxx"
#include "MACE/SimTarget/MuoniumTrack.hxx"
#include "MACE/SimTarget/RunManager.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4Track.hh"

namespace MACE::SimTarget::Action {

using namespace Geant4X::Physics::Particle;
using namespace Utility::PhysicalConstant;

TrackingAction::TrackingAction() :
    NonMoveableBase(),
    G4UserTrackingAction(),
    fMuonium(Muonium::Definition()),
    fAntiMuonium(AntiMuonium::Definition()),
    fMuoniumTrack(nullptr) {}

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    const auto* const particle = track->GetParticleDefinition();
    if (particle == fMuonium or particle == fAntiMuonium) {
        fMuoniumTrack = RunManager::Instance().GetAnalysis().NewMuoniumTrack();
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
