#include "MACE/Detector/Description/BeamDegrader.hxx"
#include "MACE/Detector/Description/BeamMonitor.hxx"
#include "MACE/Detector/Description/AcceleratorField.hxx"
#include "MACE/Detector/Description/Target.hxx"
#include "MACE/Detector/Description/World.hxx"
#include "MACE/Detector/Description/DescriptionIO.hxx"
#include "MACE/Detector/Geometry/Fast/BeamDegrader.hxx"
#include "MACE/Detector/Geometry/Fast/BeamMonitor.hxx"
#include "MACE/Detector/Geometry/Fast/Target.hxx"
#include "MACE/Detector/Geometry/Fast/World.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Messenger/DetectorMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"

#include <array>

namespace MACE::SimTarget::inline Action {

using namespace MACE::LiteralUnit::Density;
using namespace MACE::LiteralUnit::Temperature;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton(),
    G4VUserDetectorConstruction(),
    fCheckOverlap(false),
    fWorld(nullptr),
    fDensity(30_mg_cm3),
    fTemperature(293.15_K) {
    Detector::Description::DescriptionIO::Import<DescriptionInUse>(std::array{
#include "MACE/SimTarget/DefaultGeometry.inlyaml"
    });
    GeometryMessenger::Instance().AssignTo(this);
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    using namespace MACE::Detector::Geometry::Fast;

    // AcceleratorField is target's mother by default, modified it to adapt global frame
    Detector::Description::AcceleratorField::Instance().Length(0);
    Detector::Description::AcceleratorField::Instance().DownStreamLength(0);

    fWorld = std::make_shared<World>();
    auto& beamMonitor = fWorld->NewDaughter<BeamMonitor>(fCheckOverlap);
    auto& beamDegrader = fWorld->NewDaughter<BeamDegrader>(fCheckOverlap);
    auto& target = fWorld->NewDaughter<Target>(fCheckOverlap);

    auto nist = G4NistManager::Instance();
    beamMonitor.RegisterMaterial(nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"));
    beamDegrader.RegisterMaterial(nist->FindOrBuildMaterial("G4_Al"));
    target.RegisterMaterial(nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", fDensity, fTemperature));
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3, fTemperature));

    return fWorld->PhysicalVolume().get();
}

} // namespace MACE::SimTarget::inline Action
