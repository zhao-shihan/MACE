#include "MACE/Detector/Description/SelectorField.hxx"
#include "MACE/Detector/Geometry/Fast/SelectorField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void SelectorField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::SelectorField::Instance();
    const auto name = description.GetName();
    const auto radius = description.Radius();
    const auto length = description.Length();
    const auto zPosition = description.AxialPosition();

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
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, zPosition)),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Geometry::Entity::Fast
