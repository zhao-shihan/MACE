#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Geometry/Fast/EMC.h++"
#include "MACE/Detector/Geometry/Fast/World.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
// #include "MACE/SimEMC/Messenger/DetectorMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"

#include <array>

namespace MACE::SimEMC::inline Action {

using namespace MACE::LiteralUnit::Density;
using namespace MACE::LiteralUnit::Temperature;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{} {
    // Detector::Description::DescriptionIO::Import<DescriptionInUse>(
    // #include "MACE/SimEMC/DefaultGeometry.inlyaml"
    // );
    // GeometryMessenger::Instance().AssignTo(this);
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Geometry::Fast;

    fWorld = std::make_shared<World>();
    auto& emc = fWorld->NewDaughter<EMC>(fCheckOverlap);

    auto nist = G4NistManager::Instance();
    emc.RegisterMaterial(nist->FindOrBuildMaterial("G4_CESIUM_IODIDE"));
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3));

    return fWorld->PhysicalVolume().get();
}

} // namespace MACE::SimEMC::inline Action
