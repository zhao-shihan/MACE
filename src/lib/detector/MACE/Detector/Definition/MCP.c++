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

    const auto nist{G4NistManager::Instance()};

    { // MCP
        const auto solid{Make<G4Tubs>(
            mcp.Name(),
            0,
            mcp.Diameter() / 2,
            mcp.Thickness() / 2,
            0,
            2_pi)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_LEAD", 3.73_g_cm3),
            mcp.Name())};
        Make<G4PVPlacement>( // clang-format off
        G4Transform3D{{}, {0, 0, mcp.Thickness() / 2}}, // clang-format on
            logic,
            mcp.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
    { // Anode
        const auto name{mcp.Name() + "Anode"};
        const auto solid{Make<G4Tubs>(
            name,
            0,
            mcp.Diameter() / 2,
            mcp.AnodeThickness() / 2,
            0,
            2_pi)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            nist->FindOrBuildMaterial("G4_Al"),
            name)};
        Make<G4PVPlacement>( // clang-format off
        G4Transform3D{{}, {0, 0, mcp.Thickness() + mcp.AnodeDistance()}}, // clang-format on
            logic,
            name,
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
