#include "MACE/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::SimTarget::Action {

using namespace Utility::LiteralUnit::Length;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    NonCopyableBase(),
    G4VUserPrimaryGeneratorAction(),
    fSurfaceMuonGenerator(),
    fMuonsForEachG4Event(0) {
    fSurfaceMuonGenerator.SetVertexZ(-5_cm);
    Messenger::PrimaryGeneratorActionMessenger::Instance().SetTo(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        fSurfaceMuonGenerator.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimTarget::Action
