#include "MACE/Detector/Description/EMCal.h++"
#include "MACE/Detector/Geometry/Fast/EMCal.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void EMCal::Construct(G4bool checkOverlaps) {
    const auto& description = Description::EMCal::Instance();
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
        twopi);
    auto front = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        twopi);
    auto back = Make<G4Tubs>(
        "_temp",
        0,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        twopi);
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
