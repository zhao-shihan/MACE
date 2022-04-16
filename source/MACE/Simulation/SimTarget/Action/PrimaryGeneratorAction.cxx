#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Simulation::SimTarget::Action {

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    fSurfaceMuonPGA.GeneratePrimaries(event);
}

} // namespace MACE::Simulation::SimTarget::Action
