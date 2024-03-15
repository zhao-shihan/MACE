#include "MACE/Detector/Definition/Filter.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/RotationZ.h"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include <cmath>

namespace MACE::Detector::Definition {

using namespace LiteralUnit::Angle;
using namespace LiteralUnit::Length;
using namespace LiteralUnit::MathConstantSuffix;

bool Filter::Enabled() const {
    return Description::Filter::Instance().Enabled();
}

auto Filter::Construct(G4bool checkOverlaps) -> void {
    const auto& filter{Description::Filter::Instance()};

    for (auto i = 0; i < filter.Count(); ++i) {
        const auto x{(-filter.Radius() + filter.Interval() / 2) + i * filter.Interval()};
        const auto halfWidth{std::sqrt(Math::Pow<2>(filter.Radius()) - Math::Pow<2>(x))};
        const auto solid = Make<G4Box>(
            "",
            filter.Thickness() / 2,
            halfWidth,
            filter.Length() / 2);
        const auto logic = Make<G4LogicalVolume>(
            solid,
            G4NistManager::Instance()->FindOrBuildMaterial(filter.MaterialName()),
            filter.Name());
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {x, 0, 0}}, // clang-format on
            logic,
            filter.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
