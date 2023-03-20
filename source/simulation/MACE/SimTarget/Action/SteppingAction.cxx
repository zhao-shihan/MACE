#include "MACE/Extension/Geant4X/Physics/Particle/Antimuonium.hxx"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Messenger/ActionMessenger.hxx"

#include "G4MuonPlus.hh"
#include "G4Step.hh"

#include "gsl/gsl"

namespace MACE::SimTarget::inline Action {

SteppingAction::SteppingAction() :
    FreeSingleton(),
    G4UserSteppingAction(),
    fMuonPlus(gsl::not_null(G4MuonPlus::Definition())),
    fMuonium(gsl::not_null(Geant4X::Physics::Muonium::Definition())),
    fAntimuonium(gsl::not_null(Geant4X::Physics::Antimuonium::Definition())),
    fKillIrrelevants(false) {
    ActionMessenger::Instance().AssignTo(this);
}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    if (fKillIrrelevants) {
        const auto particle = step->GetTrack()->GetParticleDefinition();
        if (particle != fMuonPlus and particle != fMuonium and particle != fAntimuonium) {
            step->GetTrack()->SetTrackStatus(fStopAndKill);
        }
    }
}

} // namespace MACE::SimTarget::inline Action
