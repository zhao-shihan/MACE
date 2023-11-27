#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Geometry/Fast/Filter.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/RotationZ.h"

#include "G4Box.hh"
#include "G4MultiUnion.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"

#include <cmath>

namespace MACE::Detector::Geometry::Fast {

using namespace LiteralUnit::Angle;
using namespace LiteralUnit::Length;
using namespace LiteralUnit::MathConstantSuffix;

void Filter::Construct(G4bool checkOverlaps) {
    const auto& multiplateCollimator = Description::Filter::Instance();
    const auto name = multiplateCollimator.Name();
    const auto halfLength = multiplateCollimator.Length() / 2;
    const auto halfWidth = multiplateCollimator.Width() / 2;
    const auto halfThickness = multiplateCollimator.Thickness() / 2;
    const auto count = multiplateCollimator.Count();
    const auto spacing = multiplateCollimator.Width() / (count - 1);

    const auto solid = Make<G4Box>(
        "",
        halfThickness,
        halfWidth,
        halfLength);
    const auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    for (auto i = 0; i < count; ++i) {
        Make<G4PVPlacement>(
            G4Transform3D({}, {-halfWidth + i * spacing, 0, 0}),
            logic,
            name,
            Mother().LogicalVolume().get(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Geometry::Fast
