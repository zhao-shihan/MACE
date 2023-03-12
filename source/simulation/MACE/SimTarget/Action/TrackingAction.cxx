#include "MACE/Extension/Geant4X/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/SimTarget/Action/TrackingAction.hxx"
#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/MuoniumTrack.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4Track.hh"

namespace MACE::SimTarget::Action {

using namespace Geant4X::Physics::Particle;
using namespace PhysicalConstant;

TrackingAction::TrackingAction() :
    FreeSingleton(),
    G4UserTrackingAction(),
    fMuonium(Muonium::Definition()),
    fAntiMuonium(AntiMuonium::Definition()),
    fMuoniumTrack(nullptr),
    fEventID(-1) {}

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    if (const auto particle = track->GetParticleDefinition();
        particle == fMuonium or particle == fAntiMuonium) {
        fMuoniumTrack = Analysis::Instance().NewMuoniumTrack();
        fMuoniumTrack->VertexTime(track->GetGlobalTime());
        fMuoniumTrack->VertexPosition(track->GetPosition());
        fMuoniumTrack->VertexMomentum(track->GetMomentum());
        fMuoniumTrack->Particle(particle->GetParticleName());
        fMuoniumTrack->G4EventID(fEventID);
        fMuoniumTrack->G4TrackID(track->GetTrackID());
    }
}

void TrackingAction::PostUserTrackingAction(const G4Track* track) {
    if (const auto particle = track->GetParticleDefinition();
        particle == fMuonium or particle == fAntiMuonium) {
        fMuoniumTrack->DecayTime(track->GetGlobalTime());
        fMuoniumTrack->DecayPosition(track->GetPosition());
        fMuoniumTrack->DecayMomentum(track->GetMomentum());
    }
}

} // namespace MACE::SimTarget::Action
