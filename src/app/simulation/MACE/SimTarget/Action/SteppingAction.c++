#include "MACE/SimTarget/Action/SteppingAction.h++"

#include "Mustard/Extension/Geant4X/Particle/Antimuonium.h++"
#include "Mustard/Extension/Geant4X/Particle/Muonium.h++"

#include "G4MuonPlus.hh"
#include "G4Step.hh"

#include "gsl/gsl"

namespace MACE::SimTarget::inline Action {

SteppingAction::SteppingAction() :
    PassiveSingleton{},
    G4UserSteppingAction{},
    fMuonPlus{gsl::not_null{G4MuonPlus::Definition()}},
    fMuonium{gsl::not_null{Mustard::Geant4X::Muonium::Definition()}},
    fAntimuonium{gsl::not_null{Mustard::Geant4X::Antimuonium::Definition()}},
    fKillIrrelevants{false},
    fMessengerRegister{this} {}

auto SteppingAction::UserSteppingAction(const G4Step* step) -> void {
    if (fKillIrrelevants) {
        const auto particle = step->GetTrack()->GetParticleDefinition();
        if (particle != fMuonPlus and particle != fMuonium and particle != fAntimuonium) {
            step->GetTrack()->SetTrackStatus(fStopAndKill);
        }
    }
}

} // namespace MACE::SimTarget::inline Action
