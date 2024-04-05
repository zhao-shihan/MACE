#include "MACE/Detector/Definition/SolenoidFieldB2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationX.h"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Torus.hh"

namespace MACE::Detector::Definition {

using namespace MathConstant;

auto SolenoidFieldB2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{"SolenoidFieldB2"};

    auto solid = Make<G4Torus>(
        name,
        0,
        solenoid.FieldRadius(),
        solenoid.B2Radius(),
        -pi / 2,
        pi / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D{CLHEP::HepRotationX{pi / 2}, VectorCast<G4ThreeVector>(solenoid.B2Center())},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
