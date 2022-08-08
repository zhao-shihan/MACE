#include "MACE/Geant4X/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Messenger/ActionMessenger.hxx"

#include "G4MuonPlus.hh"
#include "G4Step.hh"

namespace MACE::SimTarget::Action {

using namespace Geant4X::Physics::Particle;

SteppingAction::SteppingAction() :
    NonMoveableBase(),
    G4UserSteppingAction(),
    fMuonPlus(G4MuonPlus::Definition()),
    fMuonium(Muonium::Definition()),
    fAntiMuonium(AntiMuonium::Definition()),
    fKillIrrelevants(false) {
    Messenger::ActionMessenger::Instance().SetTo(this);
}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    if (fKillIrrelevants) {
        const auto* const particle = step->GetTrack()->GetParticleDefinition();
        if (particle != fMuonPlus and particle != fMuonium and particle != fAntiMuonium) {
            step->GetTrack()->SetTrackStatus(fStopAndKill);
        }
    }
}

} // namespace MACE::SimTarget::Action
