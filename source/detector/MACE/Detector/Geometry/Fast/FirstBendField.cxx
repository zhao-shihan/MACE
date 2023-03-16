#include "MACE/Detector/Description/TransportLine.hxx"
#include "MACE/Detector/Geometry/Fast/FirstBendField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void FirstBendField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "FirstBendField";
    const auto radius = description.FieldRadius();
    const auto bendRadius = description.FirstBendRadius();
    const auto transform = description.FirstBendTransform();

    auto solid = Make<G4Torus>(
        name,
        0,
        radius,
        bendRadius,
        halfpi,
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

} // namespace MACE::Geometry::Entity::Fast
