#include "MACE/Detector/Definition/AcceleratorField.h++"
#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto AcceleratorField::Construct(G4bool checkOverlaps) -> void {
    const auto& accelerator{Description::Accelerator::Instance()};
    const auto name{accelerator.Name() + "Field"};

    const auto solid{Make<G4Tubs>(
        name,
        0,
        accelerator.Radius(),
        (accelerator.UpstreamLength() + accelerator.AccelerateLength()) / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        nullptr,
        name)};
    Make<G4PVPlacement>( // clang-format off
        G4Transform3D{{}, {0, 0, (accelerator.AccelerateLength() - accelerator.UpstreamLength()) / 2}}, // clang-format on
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
