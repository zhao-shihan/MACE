#include "MACE/Detector/Definition/SolenoidShieldS2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SolenoidShield.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidShieldS2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto& shield{Description::SolenoidShield::Instance()};
    const auto name{shield.Name() + "S2"};

    const auto solid{Make<G4Tubs>(
        name,
        shield.InnerRadius(),
        shield.OuterRadius(),
        solenoid.S2Length() / 2,
        0,
        2_pi)};

    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(shield.MaterialName()),
        name)};

    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
