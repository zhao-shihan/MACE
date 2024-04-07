#include "MACE/Detector/Definition/SolenoidS2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Math/LLPiecewise.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidS2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "S2"};

    const auto solid{Make<G4Tubs>(
        name,
        solenoid.InnerRadius(),
        solenoid.OuterRadius(),
        solenoid.CoilThickness() / 2,
        0,
        2_pi)};

    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(solenoid.MaterialName()),
        name)};

    const auto nCoil{Math::LLTrunc(solenoid.S2Length() / (solenoid.CoilThickness() + solenoid.ReferenceCoilSpacing()))};
    const auto spacing{solenoid.S2Length() / nCoil - solenoid.ReferenceCoilSpacing()};
    const auto z0{-solenoid.S2Length() / 2 + spacing / 2 + solenoid.CoilThickness() / 2};
    for (int k{}; k < nCoil; ++k) {
        Make<G4PVPlacement>(
            G4TranslateZ3D{z0 + k * (spacing + solenoid.CoilThickness())},
            logic,
            name,
            Mother().LogicalVolume(),
            false,
            k,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
