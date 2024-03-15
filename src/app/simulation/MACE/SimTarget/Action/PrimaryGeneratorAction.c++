#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::SimTarget::inline Action {

using namespace LiteralUnit::Length;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fSurfaceMuonGenerator{},
    fPrimariesForEachG4Event{10},
    fMessengerRegister{this} {}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    for (G4int i{}; i < fPrimariesForEachG4Event; ++i) {
        fSurfaceMuonGenerator.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimTarget::inline Action
