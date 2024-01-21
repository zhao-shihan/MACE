#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::SimTarget::inline Action {

using namespace LiteralUnit::Length;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton(),
    G4VUserPrimaryGeneratorAction(),
    fSurfaceMuonGenerator(),
    fMuonsForEachG4Event(0) {
    fSurfaceMuonGenerator.PositionZ(-5_cm);
    PrimaryGeneratorActionMessenger::Instance().Register(this);
}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        fSurfaceMuonGenerator.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimTarget::inline Action
