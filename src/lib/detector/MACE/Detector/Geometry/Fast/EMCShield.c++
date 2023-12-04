#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Geometry/Fast/EMCShield.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

auto EMCShield::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::EMCShield::Instance();
    const auto name = description.Name();
    const auto innerRadius = description.InnerRadius();
    const auto innerLength = description.InnerLength();
    const auto windowRadius = description.WindowRadius();
    const auto thickness = description.Thickness();
    const auto transform = description.CalcTransform();

    const auto body = Make<G4Tubs>(
        "_temp",
        innerRadius,
        innerRadius + thickness,
        innerLength / 2,
        0,
        2 * pi);
    const auto cap = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + thickness,
        thickness / 2,
        0,
        2 * pi);
    const auto temp = Make<G4UnionSolid>(
        "_temp",
        body,
        cap,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, -innerLength / 2 - thickness / 2)));
    const auto solid = Make<G4UnionSolid>(
        name,
        temp,
        cap,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, innerLength / 2 + thickness / 2)));
    const auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        transform,
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
