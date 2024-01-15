#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Geometry/Fast/Filter.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/RotationZ.h"

#include "G4Box.hh"
#include "G4PVPlacement.hh"

#include <cmath>

namespace MACE::Detector::Geometry::Fast {

using namespace LiteralUnit::Angle;
using namespace LiteralUnit::Length;
using namespace LiteralUnit::MathConstantSuffix;

auto Filter::Construct(G4bool checkOverlaps) -> void {
    const auto& filter = Description::Filter::Instance();
    const auto name = filter.Name();
    const auto halfLength = filter.Length() / 2;
    const auto radius = filter.Radius();
    const auto halfThickness = filter.Thickness() / 2;
    const auto count = filter.Count();
    const auto spacing = 2 * radius / count;

    for (auto i = 0; i < count; ++i) {
        const auto x{(-radius + spacing / 2) + i * spacing};
        const auto halfWidth{std::sqrt(Math::Pow<2>(radius) - Math::Pow<2>(x))};
        const auto solid = Make<G4Box>(
            "",
            halfThickness,
            halfWidth,
            halfLength);
        const auto logic = Make<G4LogicalVolume>(
            solid,
            nullptr,
            name);
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {x, 0, 0}}, // clang-format on
            logic,
            name,
            Mother().LogicalVolume().get(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Geometry::Fast
