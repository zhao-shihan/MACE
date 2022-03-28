#include "Core/Geometry/Description/VertexDetector.hxx"
#include "Core/Geometry/Entity/Fast/VertexDetector.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Geometry::Entity::Fast::VertexDetector;
using namespace MACE::Utility::LiteralUnit::Density;

void VertexDetector::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::VertexDetector::Instance();
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
