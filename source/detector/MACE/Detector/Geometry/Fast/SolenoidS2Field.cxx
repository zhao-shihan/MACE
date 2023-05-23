#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS2Field.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void SolenoidS2Field::Construct(G4bool checkOverlaps) {
    const auto& description = Description::Solenoid::Instance();
    const auto name = "SolenoidS2Field";
    const auto length = description.S2Length();
    const auto radius = description.FieldRadius();
    const auto transform = description.S2Transform();

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
