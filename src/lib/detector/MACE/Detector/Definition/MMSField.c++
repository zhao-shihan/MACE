#include "MACE/Detector/Definition/MMSField.h++"
#include "MACE/Detector/Description/MMSField.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto MMSField::Construct(G4bool checkOverlaps) -> void {
    const auto& mmsField{Description::MMSField::Instance()};

    const auto mother{Mother().LogicalVolume()};
    const auto solid{Make<G4Tubs>(
        mmsField.Name(),
        0,
        mmsField.Radius(),
        mmsField.Length() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        mother->GetMaterial(),
        mmsField.Name())};
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        mmsField.Name(),
        mother,
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
