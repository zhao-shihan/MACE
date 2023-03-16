#include "MACE/Detector/Description/TransportLine.hxx"
#include "MACE/Detector/Geometry/Fast/ThirdTransportField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void ThirdTransportField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "ThirdTransportField";
    const auto length = description.ThirdStraightLength();
    const auto radius = description.FieldRadius();
    const auto transform = description.ThirdStraightTransform();

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
