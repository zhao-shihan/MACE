#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"

namespace MACE::Simulation::SimTarget::Action {

using namespace MACE::Utility::LiteralUnit::Density;
using namespace MACE::Utility::LiteralUnit::Temperature;

DetectorConstruction::DetectorConstruction() :
    fTarget(nullptr),
    fWorld(nullptr),
    fDensity(30_mg_cm3),
    fTemperature(293.15_K) {
    Messenger::GeometryMessenger::Instance().SetTo(this);
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    using namespace MACE::Core::Geometry;

    // LinacField is target's mother by default, modified it to adapt global frame
    Description::LinacField::Instance().SetLength(0);
    Description::LinacField::Instance().SetDownStreamLength(0);

    fBeamCounter = std::make_shared<BeamCounter>();
    fBeamDegrader = std::make_shared<BeamDegrader>();
    fTarget = std::make_shared<Target>();
    fWorld = std::make_shared<World>();
    fWorld->AddDaughter(fBeamCounter);
    fWorld->AddDaughter(fBeamDegrader);
    fWorld->AddDaughter(fTarget);
    fWorld->ConstructSelfAndDescendants(fCheckOverlaps);

    auto nist = G4NistManager::Instance();
    fBeamCounter->RegisterMaterial(nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"));
    fBeamDegrader->RegisterMaterial(nist->FindOrBuildMaterial("G4_MYLAR"));
    fTarget->RegisterMaterial(nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", fDensity, fTemperature));
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3, fTemperature));

    return fWorld->GetPhysicalVolume();
}

} // namespace MACE::Simulation::SimTarget::Action
