#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/VertexDetector.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfCalorimeterField/VertexDetector.hxx"

using namespace MACE::Geometry::Entity::Fast;

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
    auto physics = Make<G4PVPlacement>(
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
