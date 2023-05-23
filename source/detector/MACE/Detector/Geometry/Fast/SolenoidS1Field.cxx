#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS1Field.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void SolenoidS1Field::Construct(G4bool checkOverlaps) {
    const auto& description = Description::Solenoid::Instance();
    const auto name = "SolenoidS1Field";
    const auto radius = description.FieldRadius();
    const auto length = description.S1Length();
    const auto transform = description.S1Transform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
        length / 2,
        0,
        twopi);
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
