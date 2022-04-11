#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"

namespace MACE::Simulation::SimTarget::Action {

G4VPhysicalVolume* DetectorConstruction::Construct() {
    using namespace MACE::Core::Geometry;
    using namespace MACE::Utility::LiteralUnit::Density;

    // LinacField is target's mother by default, modified it to adapt global frame
    Description::LinacField::Instance().SetLength(0);
    Description::LinacField::Instance().SetDownStreamLength(0);

    fTarget = std::make_shared<Target>();
    fWorld = std::make_shared<World>();
    fWorld->AddDaughter(fTarget);
    fWorld->ConstructSelfAndDescendants(fCheckOverlaps);

    auto nist = G4NistManager::Instance();
    fTargetMaterial = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);
    fTarget->RegisterMaterial(fTargetMaterial);
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3));

    return fWorld->GetPhysicalVolume();
}

} // namespace MACE::Simulation::SimTarget::Action
