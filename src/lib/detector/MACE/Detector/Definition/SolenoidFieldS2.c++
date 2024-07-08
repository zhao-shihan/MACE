#include "MACE/Detector/Definition/SolenoidFieldS2.h++"
#include "MACE/Detector/Description/Solenoid.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationY.h"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto SolenoidFieldS2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "FieldS2"};

    const auto mother{Mother().LogicalVolume()};
    const auto solid{Make<G4Tubs>(
        name,
        0,
        solenoid.FieldRadius(),
        solenoid.S2Length() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        mother->GetMaterial(),
        name)};
    Make<G4PVPlacement>(
        G4Transform3D{CLHEP::HepRotationY{0.5_pi}, Mustard::VectorCast<G4ThreeVector>(solenoid.S2Center())},
        logic,
        name,
        mother,
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
