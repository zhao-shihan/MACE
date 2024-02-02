#include "MACE/Detector/Definition/EMCMagnet.h++"
#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit;

auto EMCMagnet::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::EMCMagnet::Instance();
    const auto name = description.Name();
    const auto innerRadius = description.InnerRadius();
    const auto outerRadius = description.OuterRadius();
    const auto length = description.Length();

    const auto nist = G4NistManager::Instance();

    const auto copper = nist->FindOrBuildMaterial("G4_Cu");

    const auto solid{Make<G4Tubs>(
        name,
        innerRadius,
        outerRadius,
        length / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        copper,
        name)};
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
