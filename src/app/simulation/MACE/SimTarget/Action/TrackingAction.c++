#include "MACE/SimTarget/Action/TrackingAction.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4Track.hh"

#include "gsl/gsl"

namespace MACE::SimTarget::inline Action {

using namespace PhysicalConstant;

TrackingAction::TrackingAction() :
    PassiveSingleton{},
    G4UserTrackingAction{},
    fMuoniumTrack{} {}

auto TrackingAction::PreUserTrackingAction(const G4Track* track) -> void {
    if (const auto particle{track->GetParticleDefinition()};
        particle == Muonium::Definition() or particle == Antimuonium::Definition()) {
        fMuoniumTrack = Analysis::Instance().NewMuoniumTrack();
        Get<"EvtID">(*fMuoniumTrack) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
        Get<"TrkID">(*fMuoniumTrack) = track->GetTrackID();
        Get<"PDGID">(*fMuoniumTrack) = particle->GetPDGEncoding();
        Get<"t0">(*fMuoniumTrack) = track->GetGlobalTime();
        Get<"x0">(*fMuoniumTrack) = track->GetPosition();
        Get<"Ek0">(*fMuoniumTrack) = track->GetKineticEnergy();
        Get<"p0">(*fMuoniumTrack) = track->GetMomentum();
    }
}

auto TrackingAction::PostUserTrackingAction(const G4Track* track) -> void {
    if (const auto particle{track->GetParticleDefinition()};
        particle == Muonium::Definition() or particle == Antimuonium::Definition()) {
        Get<"t">(*fMuoniumTrack) = track->GetGlobalTime();
        Get<"x">(*fMuoniumTrack) = track->GetPosition();
        Get<"Ek">(*fMuoniumTrack) = track->GetKineticEnergy();
        Get<"p">(*fMuoniumTrack) = track->GetMomentum();
    }
}

} // namespace MACE::SimTarget::inline Action
