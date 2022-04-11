#include "MACE/Simulation/SimTarget/PrimaryGeneratorAction.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Simulation::SimTarget {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    fSurfaceMuonPGA() {
    using namespace MACE::Utility::LiteralUnit::Length;
    fSurfaceMuonPGA.SetVertexZ(-10_cm);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    fSurfaceMuonPGA.GeneratePrimaries(event);
}

} // namespace MACE::Simulation::SimTarget
