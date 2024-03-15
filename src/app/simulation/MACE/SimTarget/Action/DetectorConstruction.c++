#include "MACE/Detector/Definition/BeamDegrader.h++"
#include "MACE/Detector/Definition/BeamMonitor.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/SimTarget/Messenger/DetectorMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"

#include <array>

namespace MACE::SimTarget::inline Action {

using namespace MACE::LiteralUnit::Length;
using namespace MACE::LiteralUnit::Density;
using namespace MACE::LiteralUnit::Temperature;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{true},
    fWorld{} {
    DetectorMessenger::EnsureInstantiation();
    auto& world{Detector::Description::World::Instance()};
    world.HalfXExtent(15_cm);
    world.HalfYExtent(15_cm);
    world.HalfZExtent(15_cm);
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Definition;

    // AcceleratorField is target's mother by default, modified it to adapt global frame
    Detector::Description::AcceleratorField::Instance().Length(0);
    Detector::Description::AcceleratorField::Instance().DownStreamLength(0);

    fWorld = std::make_unique<World>();
    fWorld->NewDaughter<BeamMonitor>(fCheckOverlap);
    fWorld->NewDaughter<BeamDegrader>(fCheckOverlap);
    fWorld->NewDaughter<Target>(fCheckOverlap);

    auto nist{G4NistManager::Instance()};
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3, 293_K));

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimTarget::inline Action
