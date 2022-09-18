#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Description/BeamMonitor.hxx"
#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Core/Geometry/Description/World.hxx"
#include "MACE/Core/Geometry/DescriptionIO.hxx"
#include "MACE/Core/Geometry/Entity/Fast/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Entity/Fast/BeamMonitor.hxx"
#include "MACE/Core/Geometry/Entity/Fast/Target.hxx"
#include "MACE/Core/Geometry/Entity/Fast/World.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"

namespace MACE::SimTarget::Action {

using namespace MACE::Utility::LiteralUnit::Density;
using namespace MACE::Utility::LiteralUnit::Temperature;

DetectorConstruction::DetectorConstruction() :
    FreeSingleton<DetectorConstruction>(),
    G4VUserDetectorConstruction(),
    fCheckOverlap(false),
    fBeamDegrader(nullptr),
    fBeamMonitor(nullptr),
    fTarget(nullptr),
    fWorld(nullptr),
    fDensity(30_mg_cm3),
    fTemperature(293.15_K) {
    Core::Geometry::DescriptionIO::Import<UsedDescriptions>(std::tuple{
#include "MACE/SimTarget/DefaultGeometry.inlyaml"
    });
    Messenger::GeometryMessenger::Instance().SetTo(this);
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    using namespace MACE::Core::Geometry;
    using namespace MACE::Core::Geometry::Entity::Fast;

    // LinacField is target's mother by default, modified it to adapt global frame
    Description::LinacField::Instance().Length(0);
    Description::LinacField::Instance().DownStreamLength(0);

    fBeamDegrader = std::make_shared<BeamDegrader>();
    fBeamMonitor = std::make_shared<BeamMonitor>();
    fTarget = std::make_shared<Target>();
    fWorld = std::make_shared<World>();
    fWorld->AddDaughter(fBeamMonitor);
    fWorld->AddDaughter(fBeamDegrader);
    fWorld->AddDaughter(fTarget);
    fWorld->ConstructSelfAndDescendants(fCheckOverlap);

    auto nist = G4NistManager::Instance();
    fBeamDegrader->RegisterMaterial(nist->FindOrBuildMaterial("G4_Al"));
    fBeamMonitor->RegisterMaterial(nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"));
    fTarget->RegisterMaterial(nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", fDensity, fTemperature));
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3, fTemperature));

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimTarget::Action
