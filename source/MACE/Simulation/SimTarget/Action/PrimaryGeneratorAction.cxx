#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Simulation::SimTarget::Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    fSurfaceMuonPGA() {
    using namespace MACE::Utility::LiteralUnit::Length;
    fSurfaceMuonPGA.SetVertexZ(-15_cm);
    fSurfaceMuonPGA.SetMuonsForEachG4Event(1);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    fSurfaceMuonPGA.GeneratePrimaries(event);
}

} // namespace MACE::Simulation::SimTarget::Action
