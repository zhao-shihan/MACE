#include "MACE/Detector/Definition/EMCShield.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Detector::Definition {

using namespace MathConstant;

auto EMCShield::Construct(G4bool checkOverlaps) -> void {
    const auto& emcShield{Description::EMCShield::Instance()};
    const auto name{emcShield.Name()};
    const auto& emcField{Description::EMCField::Instance()};

    const auto body = Make<G4Tubs>(
        "_temp",
        emcShield.InnerRadius(),
        emcShield.InnerRadius() + emcShield.Thickness(),
        emcShield.InnerLength() / 2,
        0,
        2 * pi);
    const auto cap = Make<G4Tubs>(
        "_temp",
        emcShield.WindowRadius(),
        emcShield.InnerRadius() + emcShield.Thickness(),
        emcShield.Thickness() / 2,
        0,
        2 * pi);
    const auto temp = Make<G4UnionSolid>(
        "_temp",
        body,
        cap, // clang-format off
        G4Transform3D{{}, {0, 0, -emcShield.InnerLength() / 2 - emcShield.Thickness() / 2}}); // clang-format on
    const auto solid = Make<G4UnionSolid>(
        name,
        temp,
        cap, // clang-format off
        G4Transform3D{{}, {0, 0, emcShield.InnerLength() / 2 + emcShield.Thickness() / 2}}); // clang-format on
    const auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D{{}, VectorCast<G4ThreeVector>(emcField.Center())},
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
