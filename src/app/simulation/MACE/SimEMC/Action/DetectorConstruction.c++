#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Geometry/Fast/EMCCrystal.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCathode.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCoupler.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTWindow.h++"
#include "MACE/Detector/Geometry/Fast/World.h++"
#include "MACE/Detector/Geometry/GeometryBase.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/PMTSD.h++"

// #include "MACE/SimEMC/Messenger/DetectorMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include <array>

namespace MACE::SimEMC::inline Action {

using namespace MACE::LiteralUnit;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{},
    fEMCSD{},
    fPMTSD{} {
    // Detector::Description::DescriptionIO::Import<DescriptionInUse>(
    // #include "MACE/SimEMC/DefaultGeometry.inlyaml"
    // );
    // GeometryMessenger::Instance().AssignTo(this);
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Geometry::Fast;

    fWorld = std::make_shared<World>();
    auto& emcCrystal = fWorld->NewDaughter<EMCCrystal>(fCheckOverlap);
    auto& emcPMTCoupler = fWorld->NewDaughter<EMCPMTCoupler>(fCheckOverlap);
    auto& emcPMTWindow = fWorld->NewDaughter<EMCPMTWindow>(fCheckOverlap);
    auto& emcPMTCathode = fWorld->NewDaughter<EMCPMTCathode>(fCheckOverlap);

    auto nist = G4NistManager::Instance();
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3));

    fEMCSD = new SD::EMCSD(emcCrystal.LogicalVolume()->GetName());
    emcCrystal.RegisterSD(fEMCSD);

    fPMTSD = new SD::PMTSD(emcPMTCathode.LogicalVolume()->GetName());
    emcPMTCathode.RegisterSD(fPMTSD);

    return fWorld->PhysicalVolume().get();
}

} // namespace MACE::SimEMC::inline Action
