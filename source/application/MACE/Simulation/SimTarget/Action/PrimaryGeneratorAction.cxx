#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/Messenger/PrimaryGeneratorActionMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Simulation::SimTarget::Action {

using namespace Utility::LiteralUnit::Length;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
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

} // namespace MACE::Simulation::SimTarget::Action
