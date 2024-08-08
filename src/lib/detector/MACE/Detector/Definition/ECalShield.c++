#include "MACE/Detector/Definition/ECalShield.h++"
#include "MACE/Detector/Description/ECalField.h++"
#include "MACE/Detector/Description/ECalShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit;

auto ECalShield::Construct(G4bool checkOverlaps) -> void {
    const auto& shield{Description::ECalShield::Instance()};
    const auto& eCalField{Description::ECalField::Instance()};
    const auto& solenoid{Description::Solenoid::Instance()};

    const auto x0{Mustard::VectorCast<G4ThreeVector>(eCalField.Center())};
    const auto pb{G4NistManager::Instance()->FindOrBuildMaterial(shield.MaterialName())};

    const auto solidBody{Make<G4Tubs>(
        shield.Name(),
        shield.InnerRadius(),
        shield.InnerRadius() + shield.Thickness(),
        shield.InnerLength() / 2,
        0,
        2_pi)};
    const auto logicalBody{Make<G4LogicalVolume>(
        solidBody,
        pb,
        shield.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{{}, x0},
        logicalBody,
        shield.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);

    const auto solidCap{Make<G4Tubs>(
        shield.Name(),
        solenoid.FieldRadius() + shield.GapAroundWindow(),
        shield.InnerRadius() + shield.Thickness(),
        shield.Thickness() / 2,
        0,
        2_pi)};
    const auto logicalCap{Make<G4LogicalVolume>(
        solidCap,
        pb,
        shield.Name())};
    const G4ThreeVector deltaXEnd{0, 0, shield.InnerLength() / 2 + shield.Thickness() / 2};
    Make<G4PVPlacement>(
        G4Transform3D{{}, x0 - deltaXEnd},
        logicalCap,
        shield.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
    Make<G4PVPlacement>(
        G4Transform3D{{}, x0 + deltaXEnd},
        logicalCap,
        shield.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
