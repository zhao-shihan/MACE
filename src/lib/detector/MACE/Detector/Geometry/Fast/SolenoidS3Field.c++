#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS3Field.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

void SolenoidS3Field::Construct(G4bool checkOverlaps) {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{"SolenoidS3Field"};

    auto solid = Make<G4Tubs>(
        name,
        0,
        solenoid.OuterRadius(),
        solenoid.S3Length() / 2,
        0,
        2 * pi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D{{}, VectorCast<G4ThreeVector>(solenoid.S3Center())},
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
