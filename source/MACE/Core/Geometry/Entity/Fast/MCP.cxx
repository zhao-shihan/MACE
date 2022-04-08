#include "MACE/Core/Geometry/Description/MCP.hxx"
#include "MACE/Core/Geometry/Entity/Fast/MCP.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Core::Geometry::Entity::Fast::MCP;
using namespace MACE::Utility::LiteralUnit::Density;

void MCP::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::MCP::Instance();
    const auto name = description.GetName();
    const auto width = description.GetWidth();
    const auto thickness = description.GetThickness();

    auto material = G4NistManager::Instance()->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);

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
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, thickness / 2)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
