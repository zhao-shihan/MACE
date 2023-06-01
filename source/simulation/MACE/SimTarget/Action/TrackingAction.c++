#include "MACE/Extension/Geant4X/Physics/Particle/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.h++"
#include "MACE/SimTarget/Action/TrackingAction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/MuoniumTrack.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4Track.hh"

#include "gsl/gsl"

namespace MACE::SimTarget::inline Action {

using namespace PhysicalConstant;

TrackingAction::TrackingAction() :
    PassiveSingleton(),
    G4UserTrackingAction(),
    fMuonium(gsl::not_null(Geant4X::Physics::Muonium::Definition())),
    fAntimuonium(gsl::not_null(Geant4X::Physics::Antimuonium::Definition())),
    fMuoniumTrack(nullptr),
    fEventID(-1) {}

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    if (const auto particle = track->GetParticleDefinition();
        particle == fMuonium or particle == fAntimuonium) {
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
        particle == fMuonium or particle == fAntimuonium) {
        fMuoniumTrack->DecayTime(track->GetGlobalTime());
        fMuoniumTrack->DecayPosition(track->GetPosition());
        fMuoniumTrack->DecayMomentum(track->GetMomentum());
    }
}

} // namespace MACE::SimTarget::inline Action
