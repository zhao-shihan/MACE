#include "MACE/Simulation/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Simulation::SimMACE::Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    fSurfaceMuonPGA() //,
/* fCosmicRayMuonPGA() */ {
    using namespace MACE::Utility::LiteralUnit::Length;
    fSurfaceMuonPGA.SetVertexZ(-1.5_m);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    fSurfaceMuonPGA.GeneratePrimaries(event);
    // fCosmicRayMuonPGA.GeneratePrimaries(event);
}

} // namespace MACE::Simulation::SimMACE::Action
