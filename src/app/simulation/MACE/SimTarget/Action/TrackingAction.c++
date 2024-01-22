#include "MACE/SimTarget/Action/TrackingAction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/MuoniumTrack.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4Track.hh"

#include "gsl/gsl"

namespace MACE::SimTarget::inline Action {

using namespace PhysicalConstant;

TrackingAction::TrackingAction() :
    PassiveSingleton{},
    G4UserTrackingAction{},
    fMuonium{gsl::not_null{Muonium::Definition()}},
    fAntimuonium{gsl::not_null{Antimuonium::Definition()}},
    fMuoniumTrack{},
    fEventID{-1} {}

auto TrackingAction::PreUserTrackingAction(const G4Track* track) -> void {
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

auto TrackingAction::PostUserTrackingAction(const G4Track* track) -> void {
    if (const auto particle = track->GetParticleDefinition();
        particle == fMuonium or particle == fAntimuonium) {
        fMuoniumTrack->DecayTime(track->GetGlobalTime());
        fMuoniumTrack->DecayPosition(track->GetPosition());
        fMuoniumTrack->DecayMomentum(track->GetMomentum());
    }
}

} // namespace MACE::SimTarget::inline Action
