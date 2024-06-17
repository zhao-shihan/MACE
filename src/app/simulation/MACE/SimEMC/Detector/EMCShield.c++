#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/SimEMC/Detector/EMCShield.h++"

#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::SimEMC::Detector {

using namespace Mustard::LiteralUnit;

auto EMCShield::Construct(G4bool checkOverlaps) -> void {
    const auto& shield{MACE::Detector::Description::EMCShield::Instance()};
    const auto& solenoid{MACE::Detector::Description::Solenoid::Instance()};

    const auto body{Make<G4Tubs>(
        "_temp",
        shield.InnerRadius(),
        shield.InnerRadius() + shield.Thickness(),
        shield.InnerLength() / 2,
        0,
        2_pi)};
    const auto cap{Make<G4Tubs>(
        "_temp",
        solenoid.FieldRadius() + shield.GapAroundWindow(),
        shield.InnerRadius() + shield.Thickness(),
        shield.Thickness() / 2,
        0,
        2_pi)}; // clang-format off
    const auto temp{Make<G4UnionSolid>(
        "_temp",
        body,
        cap,
        G4Transform3D{{}, {0, 0, -shield.InnerLength() / 2 - shield.Thickness() / 2}})};
    const auto solid{Make<G4UnionSolid>(
        shield.Name(),
        temp,
        cap,
        G4Transform3D{{}, {0, 0, shield.InnerLength() / 2 + shield.Thickness() / 2}})}; // clang-format on
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(shield.MaterialName()),
        shield.Name())};
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        shield.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::SimEMC::Detector
