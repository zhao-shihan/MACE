#include "MACE/Detector/Definition/EMCField.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::MathConstant;

auto EMCField::Construct(G4bool checkOverlaps) -> void {
    const auto& emcField{Description::EMCField::Instance()};
    auto name{emcField.Name()};

    auto solid = Make<G4Tubs>(
        name,
        0,
        emcField.Radius(),
        emcField.Length() / 2,
        0,
        2 * pi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D{{}, Mustard::VectorCast<G4ThreeVector>(emcField.Center())},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
