#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS2Field.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

void SolenoidS2Field::Construct(G4bool checkOverlaps) {
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

} // namespace MACE::Detector::Geometry::Fast
