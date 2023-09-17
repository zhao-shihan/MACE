#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB1Field.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

void SolenoidB1Field::Construct(G4bool checkOverlaps) {
    const auto& description = Description::Solenoid::Instance();
    const auto name = "SolenoidB1Field";
    const auto radius = description.FieldRadius();
    const auto bendRadius = description.B1Radius();
    const auto transform = description.B1Transform();

    auto solid = Make<G4Torus>(
        name,
        0,
        radius,
        bendRadius,
        pi / 2,
        pi / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        transform,
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
