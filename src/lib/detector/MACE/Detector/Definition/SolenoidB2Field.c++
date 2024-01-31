#include "MACE/Detector/Definition/SolenoidB2Field.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationX.h"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Torus.hh"

namespace MACE::Detector::Definition {

using namespace MathConstant;

auto SolenoidB2Field::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{"SolenoidB2Field"};

    auto solid = Make<G4Torus>(
        name,
        0,
        solenoid.OuterRadius(),
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
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
