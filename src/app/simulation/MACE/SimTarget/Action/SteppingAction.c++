#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"
#include "MACE/SimTarget/Action/SteppingAction.h++"
#include "MACE/SimTarget/Messenger/ActionMessenger.h++"

#include "G4MuonPlus.hh"
#include "G4Step.hh"

#include "gsl/gsl"

namespace MACE::SimTarget::inline Action {

SteppingAction::SteppingAction() :
    PassiveSingleton(),
    G4UserSteppingAction(),
    fMuonPlus{gsl::not_null{G4MuonPlus::Definition()}},
    fMuonium{gsl::not_null(Muonium::Definition())},
    fAntimuonium{gsl::not_null(Antimuonium::Definition())},
    fKillIrrelevants{false} {
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
