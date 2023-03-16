#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Detector/Description/TransportLine.hxx"
#include "MACE/Detector/Geometry/Fast/SecondTransportField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void SecondTransportField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "SecondTransportField";
    const auto length = description.SecondStraightLength();
    const auto radius = description.FieldRadius();
    const auto transform = description.SecondStraightTransform();

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

} // namespace MACE::Geometry::Entity::Fast
