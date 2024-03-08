#include "MACE/Detector/Definition/MCP.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace MACE::LiteralUnit;

auto MCP::Construct(G4bool checkOverlaps) -> void {
    const auto& mcp{Description::MCP::Instance()};
    const auto name{mcp.Name()};

    const auto solid{Make<G4Tubs>(
        name,
        0,
        mcp.Diameter() / 2,
        mcp.Thickness() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3),
        name)};
    Make<G4PVPlacement>( // clang-format off
        G4Transform3D{{}, {0, 0, mcp.Thickness() / 2}}, // clang-format on
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
