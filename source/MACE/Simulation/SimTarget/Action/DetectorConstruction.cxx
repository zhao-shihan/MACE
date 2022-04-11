#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"

#include "G4Box.hh"

namespace MACE::Simulation::SimTarget::Action {

G4VPhysicalVolume* DetectorConstruction::Construct() {
    using namespace MACE::Core::Geometry;

    fTarget = std::make_shared<Target>();
    fWorld = std::make_shared<World>();

    fWorld->AddDaughter(fTarget);

    fWorld->ConstructSelfAndDescendants(fCheckOverlaps);

    return fWorld->GetPhysicalVolume();
}

} // namespace MACE::Simulation::SimTarget
