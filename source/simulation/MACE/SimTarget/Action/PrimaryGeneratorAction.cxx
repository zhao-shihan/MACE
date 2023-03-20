#include "MACE/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::SimTarget::inline Action {

using namespace LiteralUnit::Length;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    FreeSingleton(),
    G4VUserPrimaryGeneratorAction(),
    fSurfaceMuonGenerator(),
    fMuonsForEachG4Event(0) {
    fSurfaceMuonGenerator.PositionZ(-5_cm);
    PrimaryGeneratorActionMessenger::Instance().AssignTo(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        fSurfaceMuonGenerator.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimTarget::inline Action
