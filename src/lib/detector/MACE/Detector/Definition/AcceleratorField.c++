#include "MACE/Detector/Definition/AcceleratorField.h++"
#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto AcceleratorField::Construct(G4bool checkOverlaps) -> void {
    const auto& field{Description::AcceleratorField::Instance()};

    const auto solid{Make<G4Tubs>(
        field.Name(),
        0,
        field.Radius(),
        (field.UpstreamLength() + field.AccelerateLength()) / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        nullptr,
        field.Name())};
    Make<G4PVPlacement>( // clang-format off
        G4Transform3D{{}, {0, 0, (field.AccelerateLength() - field.UpstreamLength()) / 2}}, // clang-format on
        logic,
        field.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
