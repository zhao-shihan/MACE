#include "MACE/Detector/Definition/SolenoidFieldT2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Torus.hh"
#include "G4Transform3D.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto SolenoidFieldT2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "FieldT2"};

    const auto solid{Make<G4Torus>(
        name,
        0,
        solenoid.FieldRadius(),
        solenoid.T2Radius(),
        0,
        0.5_pi)};

    const auto logic{Make<G4LogicalVolume>(
        solid,
        nullptr,
        name)};

    Make<G4PVPlacement>(
        G4Translate3D{Mustard::VectorCast<G4ThreeVector>(solenoid.T2Center())} * G4RotateX3D{-0.5_pi},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
