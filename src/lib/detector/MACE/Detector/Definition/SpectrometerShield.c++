#include "MACE/Detector/Definition/SpectrometerShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit;

auto SpectrometerShield::Construct(G4bool checkOverlaps) -> void {
    const auto& shield{Description::SpectrometerShield::Instance()};
    const auto& solenoid{Description::Solenoid::Instance()};

    auto body{Make<G4Tubs>(
        "_temp",
        shield.InnerRadius(),
        shield.InnerRadius() + shield.Thickness(),
        shield.InnerLength() / 2,
        0,
        2_pi)};
    auto cap{Make<G4Tubs>(
        "_temp",
        solenoid.FieldRadius() + shield.GapAroundWindow(),
        shield.InnerRadius() + shield.Thickness(),
        shield.Thickness() / 2,
        0,
        2_pi)}; // clang-format off
    auto solid{Make<G4UnionSolid>(
            shield.Name(),
            body,
            cap, 
        G4Transform3D{{}, {0, 0, -shield.InnerLength() / 2 - shield.Thickness() / 2}})}; // clang-format on
    auto logic{Make<G4LogicalVolume>(
        solid,
        nullptr,
        shield.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        shield.Name(),
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
