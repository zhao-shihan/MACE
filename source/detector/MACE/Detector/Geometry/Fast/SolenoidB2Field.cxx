#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidB2Field.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void SolenoidB2Field::Construct(G4bool checkOverlaps) {
    const auto& description = Description::Solenoid::Instance();
    const auto name = "SolenoidB2Field";
    const auto radius = description.FieldRadius();
    const auto bendRadius = description.B2Radius();
    const auto transform = description.B2Transform();

    auto solid = Make<G4Torus>(
        name,
        0,
        radius,
        bendRadius,
        -halfpi,
        halfpi);
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
