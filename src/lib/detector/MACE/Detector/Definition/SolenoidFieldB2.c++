#include "MACE/Detector/Definition/SolenoidFieldB2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Torus.hh"
#include "G4Transform3D.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidFieldB2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "FieldB2"};

    const auto solid{Make<G4Torus>(
        name,
        0,
        solenoid.FieldRadius(),
        solenoid.B2Radius(),
        0,
        0.5_pi)};

    const auto logic{Make<G4LogicalVolume>(
        solid,
        nullptr,
        name)};

    Make<G4PVPlacement>(
        G4Translate3D{VectorCast<G4ThreeVector>(solenoid.B2Center())} * G4RotateX3D{-0.5_pi},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
