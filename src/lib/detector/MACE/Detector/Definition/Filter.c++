#include "MACE/Detector/Definition/Filter.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/RotationZ.h"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "muc/math"

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

    const auto x0{-(filter.Count() - 1) * filter.Pitch() / 2};
    for (int k{}; k < filter.Count(); ++k) {
        const auto x{x0 + k * filter.Pitch()};
        const auto halfWidth{std::sqrt(muc::pow<2>(filter.Radius()) - muc::pow<2>(x))};

        const auto solid{Make<G4Box>(
            "",
            filter.Thickness() / 2,
            halfWidth,
            filter.Length() / 2)};

        const auto logic{Make<G4LogicalVolume>(
            solid,
            G4NistManager::Instance()->FindOrBuildMaterial(filter.MaterialName()),
            filter.Name())};

        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {x, 0, 0}}, // clang-format on
            logic,
            filter.Name(),
            Mother().LogicalVolume(),
            false,
            k,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
