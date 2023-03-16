#include "MACE/Detector/Description/TransportLine.hxx"
#include "MACE/Detector/Geometry/Fast/ThirdTransportSolenoid.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void ThirdTransportSolenoid::Construct(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "ThirdTransportSolenoid";
    const auto innerRadius = description.SolenoidInnerRadius();
    const auto outerRadius = description.SolenoidOuterRadius();
    const auto length = description.ThirdStraightLength();

    auto solid = Make<G4Tubs>(
        name,
        innerRadius,
        outerRadius,
        length / 2,
        0,
        twopi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Geometry::Entity::Fast
