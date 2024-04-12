#include "MACE/Detector/Definition/TTC.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/Math/Parity.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"

#include "fmt/format.h"

namespace MACE::Detector::Definition {

using namespace MACE::LiteralUnit::MathConstantSuffix;

auto TTC::Construct(G4bool checkOverlaps) -> void {
    const auto& ttc{Description::TTC::Instance()};

    const auto solid{Make<G4Box>(
        ttc.Name(),
        ttc.Thickness() / 2,
        ttc.Length() / 2,
        ttc.Width() / 2)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->BuildMaterialWithNewDensity("TTC_PS101", "G4_POLYSTYRENE", ttc.Density()),
        ttc.Name())};
    int tileID{};
    const auto deltaPhi{2_pi / ttc.NAlongPhi()};
    for (int i{}; i < ttc.NAlongZ(); ++i) { // clang-format off
        const auto transform{G4RotateZ3D{Math::IsEven(i) ? 0 : deltaPhi / 2} *
                             G4Translate3D{ttc.Radius(), 0, (1 - ttc.NAlongZ()) * ttc.Width() / 2 + i * ttc.Width()} *
                             G4RotateZ3D{Math::IsEven(i) ? ttc.SlantAngle() : -ttc.SlantAngle()}}; // clang-format on
        for (int j{}; j < ttc.NAlongPhi(); ++j, ++tileID) {
            Make<G4PVPlacement>(
                G4RotateZ3D{j * deltaPhi} * transform,
                logic,
                fmt::format("{}_{}", ttc.Name(), tileID),
                Mother().LogicalVolume(),
                false,
                tileID,
                checkOverlaps);
        }
    }
}

} // namespace MACE::Detector::Definition
