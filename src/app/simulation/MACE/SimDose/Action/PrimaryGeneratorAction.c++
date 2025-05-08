#include "MACE/SimDose/Action/PrimaryGeneratorAction.h++"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"

namespace MACE::SimDose::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{this},
    G4VUserPrimaryGeneratorAction{},
    fGPSX{} {}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    fGPSX.GeneratePrimaryVertex(event);
}

} // namespace MACE::SimDose::inline Action
