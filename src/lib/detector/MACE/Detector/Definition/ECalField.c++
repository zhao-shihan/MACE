#include "MACE/Detector/Definition/ECalField.h++"
#include "MACE/Detector/Description/ECalField.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto ECalField::Construct(G4bool checkOverlaps) -> void {
    const auto& eCalField{Description::ECalField::Instance()};

    const auto mother{Mother().LogicalVolume()};
    const auto solid{Make<G4Tubs>(
        eCalField.Name(),
        0,
        eCalField.Radius(),
        eCalField.Length() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        mother->GetMaterial(),
        eCalField.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{{}, Mustard::VectorCast<G4ThreeVector>(eCalField.Center())},
        logic,
        eCalField.Name(),
        mother,
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
