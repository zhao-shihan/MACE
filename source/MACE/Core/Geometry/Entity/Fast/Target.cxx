#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Core/Geometry/Entity/Fast/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Core::Geometry::Entity::Fast::Target;
using namespace MACE::Utility::LiteralUnit::Density;

void Target::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::Target::Instance();
    const auto name = description.GetName();
    const auto width = description.GetWidth();
    const auto thickness = description.GetThickness();
    const auto transform = description.GetTransform();

    auto material = G4NistManager::Instance()->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);

    auto solid = Make<G4Box>(
        name,
        width / 2,
        width / 2,
        thickness / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    Make<G4PVPlacement>(
        transform,
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
