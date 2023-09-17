#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/Simulation/SimTarget/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::inline Simulation::SimTarget::inline Action {

using namespace LiteralUnit::Length;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton(),
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

} // namespace MACE::inline Simulation::SimTarget::inline Action
