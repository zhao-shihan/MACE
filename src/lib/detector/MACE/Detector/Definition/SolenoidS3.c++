#include "MACE/Detector/Definition/SolenoidS3.h++"
#include "MACE/Detector/Description/Solenoid.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include "muc/math"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto SolenoidS3::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "S3"};

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

    const auto nCoil{muc::lltrunc((solenoid.S3Length() - solenoid.ReferenceCoilSpacing() / 2) /
                                  (solenoid.CoilThickness() + solenoid.ReferenceCoilSpacing()))};
    const auto z0{-solenoid.S3Length() / 2 + solenoid.ReferenceCoilSpacing() / 2 + solenoid.CoilThickness() / 2};
    for (int k{}; k < nCoil; ++k) {
        Make<G4PVPlacement>(
            G4TranslateZ3D{z0 + k * (solenoid.ReferenceCoilSpacing() + solenoid.CoilThickness())},
            logic,
            name,
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
