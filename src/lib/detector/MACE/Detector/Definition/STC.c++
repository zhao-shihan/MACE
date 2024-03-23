#include "MACE/Detector/Definition/STC.h++"
#include "MACE/Detector/Description/STC.h++"
#include "MACE/Math/Parity.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"

#include "fmt/format.h"

namespace MACE::Detector::Definition {

using namespace MACE::LiteralUnit::MathConstantSuffix;

auto STC::Construct(G4bool checkOverlaps) -> void {
    const auto& stc{Description::STC::Instance()};

    const auto solid{Make<G4Box>(
        stc.Name(),
        stc.Thickness() / 2,
        stc.Length() / 2,
        stc.Width() / 2)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->BuildMaterialWithNewDensity("STC_PS101", "G4_POLYSTYRENE", stc.Density()),
        stc.Name())};
    int detectorID{};
    const auto deltaPhi{2_pi / stc.NAlongPhi()};
    for (int i{}; i < stc.NAlongZ(); ++i) { // clang-format off
        const auto transform{G4RotateZ3D{Math::IsEven(i) ? 0 : deltaPhi / 2} *
                             G4Translate3D{stc.Radius(), 0, (1 - stc.NAlongZ()) * stc.Width() / 2 + i * stc.Width()} *
                             G4RotateZ3D{Math::IsEven(i) ? stc.SlantAngle() : -stc.SlantAngle()}}; // clang-format on
        for (int j{}; j < stc.NAlongPhi(); ++j, ++detectorID) {
            Make<G4PVPlacement>(
                G4RotateZ3D{j * deltaPhi} * transform,
                logic,
                fmt::format("{}_{}", stc.Name(), detectorID),
                Mother().LogicalVolume(),
                false,
                detectorID,
                checkOverlaps);
        }
    }
}

} // namespace MACE::Detector::Definition
