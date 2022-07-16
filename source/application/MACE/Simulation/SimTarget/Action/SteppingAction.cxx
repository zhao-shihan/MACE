#include "MACE/Simulation/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Particle/Muonium.hxx"
#include "MACE/Simulation/SimTarget/Action/SteppingAction.hxx"
#include "MACE/Simulation/SimTarget/Messenger/ActionMessenger.hxx"

#include "G4MuonPlus.hh"
#include "G4Step.hh"

namespace MACE::Simulation::SimTarget::Action {

using namespace Physics::Particle;

SteppingAction::SteppingAction() :
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

} // namespace MACE::Simulation::SimTarget::Action
