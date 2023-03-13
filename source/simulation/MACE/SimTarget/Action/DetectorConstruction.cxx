#include "MACE/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Geometry/Description/BeamMonitor.hxx"
#include "MACE/Geometry/Description/LinacField.hxx"
#include "MACE/Geometry/Description/Target.hxx"
#include "MACE/Geometry/Description/World.hxx"
#include "MACE/Geometry/DescriptionIO.hxx"
#include "MACE/Geometry/Entity/Fast/BeamDegrader.hxx"
#include "MACE/Geometry/Entity/Fast/BeamMonitor.hxx"
#include "MACE/Geometry/Entity/Fast/Target.hxx"
#include "MACE/Geometry/Entity/Fast/World.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"

#include <array>

namespace MACE::SimTarget::Action {

using namespace MACE::LiteralUnit::Density;
using namespace MACE::LiteralUnit::Temperature;

DetectorConstruction::DetectorConstruction() :
    FreeSingleton(),
    G4VUserDetectorConstruction(),
    fCheckOverlap(false),
    fWorld(nullptr),
    fDensity(30_mg_cm3),
    fTemperature(293.15_K) {
    Geometry::DescriptionIO::Import<UsedDescriptions>(std::array{
#include "MACE/SimTarget/DefaultGeometry.inlyaml"
    });
    Messenger::GeometryMessenger::Instance().AssignTo(this);
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    using namespace MACE::Geometry::Entity::Fast;

    // LinacField is target's mother by default, modified it to adapt global frame
    Geometry::Description::LinacField::Instance().Length(0);
    Geometry::Description::LinacField::Instance().DownStreamLength(0);

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

} // namespace MACE::SimTarget::Action
