#include "MACE/Detector/Definition/SolenoidFieldS3.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::MathConstant;

auto SolenoidFieldS3::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{"SolenoidFieldS3"};

    auto solid = Make<G4Tubs>(
        name,
        0,
        solenoid.FieldRadius(),
        solenoid.S3Length() / 2,
        0,
        2 * pi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D{{}, Mustard::VectorCast<G4ThreeVector>(solenoid.S3Center())},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
