#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/SimPTS/Detector/Definition/VirtualDetectorD.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorD.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::SimPTS::Detector::Definition {

auto VirtualDetectorD::Construct(bool checkOverlaps) -> void {
    const auto& mcpChamber{MACE::Detector::Description::MCPChamber::Instance()};
    const auto& virtualDetectorD{Description::VirtualDetectorD::Instance()};

    const auto solid{Make<G4Tubs>(
        virtualDetectorD.Name(),
        0,
        mcpChamber.InnerRadius(),
        virtualDetectorD.Thickness() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        Mother().LogicalVolume()->GetMaterial(),
        virtualDetectorD.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        virtualDetectorD.Name(),
        Mother().LogicalVolume(),
        false,
        3,
        checkOverlaps);
}

} // namespace MACE::SimPTS::Detector::Definition
