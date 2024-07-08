#include "MACE/Detector/Definition/EMCField.h++"
#include "MACE/Detector/Description/EMCField.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto EMCField::Construct(G4bool checkOverlaps) -> void {
    const auto& emcField{Description::EMCField::Instance()};

    const auto mother{Mother().LogicalVolume()};
    const auto solid{Make<G4Tubs>(
        emcField.Name(),
        0,
        emcField.Radius(),
        emcField.Length() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        mother->GetMaterial(),
        emcField.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{{}, Mustard::VectorCast<G4ThreeVector>(emcField.Center())},
        logic,
        emcField.Name(),
        mother,
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
