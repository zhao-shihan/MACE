#include "MACE/Geant4X/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Messenger/ActionMessenger.hxx"

#include "G4MuonPlus.hh"
#include "G4Step.hh"

#include "gsl/gsl"

namespace MACE::SimTarget::Action {

using namespace Geant4X::Physics::Particle;

SteppingAction::SteppingAction() :
    FreeSingleton(),
    G4UserSteppingAction(),
    fMuonPlus(gsl::not_null(G4MuonPlus::Definition())),
    fMuonium(gsl::not_null(Muonium::Definition())),
    fAntiMuonium(gsl::not_null(AntiMuonium::Definition())),
    fKillIrrelevants(false) {
    Messenger::ActionMessenger::Instance().AssignTo(this);
}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    if (fKillIrrelevants) {
        const auto particle = step->GetTrack()->GetParticleDefinition();
        if (particle != fMuonPlus and particle != fMuonium and particle != fAntiMuonium) {
            step->GetTrack()->SetTrackStatus(fStopAndKill);
        }
    }
}

} // namespace MACE::SimTarget::Action
