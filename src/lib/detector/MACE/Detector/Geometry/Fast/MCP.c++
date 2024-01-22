#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Geometry/Fast/MCP.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Detector::Geometry::Fast::MCP;
using namespace MACE::LiteralUnit;

auto MCP::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::MCP::Instance();
    const auto name = description.Name();
    const auto width = description.Width();
    const auto thickness = description.Thickness();

    const auto nistManager = G4NistManager::Instance();
    const auto mcpMaterial = nistManager->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);

    auto solid = Make<G4Box>(
        name,
        width / 2,
        width / 2,
        thickness / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        mcpMaterial,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, thickness / 2)),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}
