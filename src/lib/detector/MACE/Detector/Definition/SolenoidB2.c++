#include "MACE/Detector/Definition/SolenoidB2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Math/LLPiecewise.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include <cmath>

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidB2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "B2"};

    const auto solid{Make<G4Tubs>(
        name,
        solenoid.InnerRadius(),
        solenoid.OuterRadius(),
        solenoid.CoilThickness() / 2,
        0,
        2_pi)};

    auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(solenoid.MaterialName()),
        name)};

    const auto referenceAngularSpacing{2 * std::asin(solenoid.ReferenceCoilSpacing() / (2 * solenoid.B2Radius()))};
    const auto coilAngularThickness{2 * std::asin(solenoid.CoilThickness() / (2 * solenoid.B2Radius()))};
    const auto nCoil{Math::LLTrunc(0.5_pi / (coilAngularThickness + referenceAngularSpacing))};
    const auto angularSpacing{0.5_pi / nCoil - referenceAngularSpacing};
    const auto phi0{angularSpacing / 2 + coilAngularThickness / 2}; // clang-format off
    const auto basicTransform{G4TranslateX3D{solenoid.B2Radius()} *
                              G4Transform3D{Mother().PhysicalVolume()->GetRotation()->inverse(), {}}}; // clang-format on
    for (int k{}; k < nCoil; ++k) {
        Make<G4PVPlacement>(
            G4RotateZ3D{phi0 + k * (angularSpacing + coilAngularThickness)} * basicTransform,
            logic,
            name,
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
