#include "MACE/Detector/Definition/SolenoidFieldS2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationY.h"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace MathConstant;

auto SolenoidFieldS2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{"SolenoidFieldS2"};

    auto solid = Make<G4Tubs>(
        name,
        0,
        solenoid.OuterRadius(),
        solenoid.S2Length() / 2,
        0,
        2 * pi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D{CLHEP::HepRotationY{pi / 2}, VectorCast<G4ThreeVector>(solenoid.S2Center())},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
