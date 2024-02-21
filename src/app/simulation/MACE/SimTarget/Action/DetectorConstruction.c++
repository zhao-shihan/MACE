#include "MACE/Detector/Definition/BeamDegrader.h++"
#include "MACE/Detector/Definition/BeamMonitor.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"

#include <array>

namespace MACE::SimTarget::inline Action {

using namespace MACE::LiteralUnit::Density;
using namespace MACE::LiteralUnit::Temperature;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{},
    fTargetDensity{27_mg_cm3},
    fTargetTemperature{293.15_K},
    fMessengerRegister{this} {
    Detector::Description::DescriptionIO::Import<DescriptionInUse>(
#include "MACE/SimTarget/DefaultGeometry.inlyaml"
    );
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Definition;

    // AcceleratorField is target's mother by default, modified it to adapt global frame
    Detector::Description::AcceleratorField::Instance().Length(0);
    Detector::Description::AcceleratorField::Instance().DownStreamLength(0);

    fWorld = std::make_unique<World>();
    auto& beamMonitor = fWorld->NewDaughter<BeamMonitor>(fCheckOverlap);
    auto& beamDegrader = fWorld->NewDaughter<BeamDegrader>(fCheckOverlap);
    auto& target = fWorld->NewDaughter<Target>(fCheckOverlap);

    auto nist = G4NistManager::Instance();
    beamMonitor.RegisterMaterial(nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"));
    beamDegrader.RegisterMaterial(nist->FindOrBuildMaterial("G4_Al"));
    target.RegisterMaterial(nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", fTargetDensity, fTargetTemperature));
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3, fTargetTemperature));

    return fWorld->PhysicalVolume().get();
}

} // namespace MACE::SimTarget::inline Action
