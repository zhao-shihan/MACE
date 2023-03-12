#include "MACE/Core/Geometry/Description/MCP.hxx"
#include "MACE/Core/Geometry/Entity/Fast/MCP.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Core::Geometry::Entity::Fast::MCP;
using namespace MACE::LiteralUnit::Density;

void MCP::Construct(G4bool checkOverlaps) {
    const auto& description = Description::MCP::Instance();
    const auto name = description.GetName();
    const auto width = description.Width();
    const auto thickness = description.Thickness();

    auto solid = Make<G4Box>(
        name,
        width / 2,
        width / 2,
        thickness / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
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
