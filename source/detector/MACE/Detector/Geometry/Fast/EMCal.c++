#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Geometry/Fast/EMC.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

void EMC::Construct(G4bool checkOverlaps) {
    const auto& description = Description::EMC::Instance();
    const auto name = description.Name();
    const auto innerRadius = description.InnerRadius();
    const auto innerLength = description.InnerLength();
    const auto windowRadius = description.WindowRadius();
    const auto crystalLength = description.CrystalLength();

    auto body = Make<G4Tubs>(
        "_temp",
        innerRadius,
        innerRadius + crystalLength,
        innerLength / 2,
        0,
        2 * pi);
    auto front = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        2 * pi);
    auto back = Make<G4Tubs>(
        "_temp",
        0,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        2 * pi);
    auto temp = Make<G4UnionSolid>(
        "_temp",
        body,
        front,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, -innerLength / 2 - crystalLength / 2)));
    auto solid = Make<G4UnionSolid>(
        name,
        temp,
        back,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, innerLength / 2 + crystalLength / 2)));
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
