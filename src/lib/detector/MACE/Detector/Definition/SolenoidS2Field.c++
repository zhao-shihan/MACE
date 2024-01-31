#include "MACE/Detector/Definition/SolenoidS2Field.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationY.h"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace MathConstant;

auto SolenoidS2Field::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{"SolenoidS2Field"};

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
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
