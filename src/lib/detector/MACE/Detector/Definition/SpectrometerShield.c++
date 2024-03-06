#include "MACE/Detector/Definition/SpectrometerShield.h++"
#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

#include <cmath>

namespace MACE::Detector::Definition {

using namespace LiteralUnit;

auto SpectrometerShield::Construct(G4bool checkOverlaps) -> void {
    const auto& shield{Description::SpectrometerShield::Instance()};

    const auto pb{G4NistManager::Instance()->FindOrBuildMaterial(shield.MaterialName())};

    const auto solidBody{Make<G4Tubs>(
        shield.Name(),
        shield.InnerRadius(),
        shield.InnerRadius() + shield.Thickness(),
        shield.InnerLength() / 2,
        0,
        2_pi)};
    const auto logicBody{Make<G4LogicalVolume>(
        solidBody,
        pb,
        shield.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logicBody,
        shield.Name(),
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);

    const auto zCap{shield.InnerLength() / 2 + shield.Thickness() / 2};
    const auto solidCap{Make<G4SubtractionSolid>(
        shield.Name(),
        Make<G4Tubs>(
            "_temp",
            0,
            shield.InnerRadius() + shield.Thickness(),
            shield.Thickness() / 2,
            0,
            2_pi),
        Make<G4Tubs>(
            "_temp",
            0,
            shield.WindowRadius(),
            shield.Thickness(),
            0,
            2_pi),
        nullptr,
        G4ThreeVector{zCap * std::tan(shield.BeamSlantAngle()), 0, 0})};
    const auto logicCap{Make<G4LogicalVolume>(
        solidCap,
        pb,
        shield.Name())};
    Make<G4PVPlacement>( // clang-format off
        G4Transform3D{{}, {0, 0, -zCap}}, // clang-format on
        logicCap,
        shield.Name(),
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
