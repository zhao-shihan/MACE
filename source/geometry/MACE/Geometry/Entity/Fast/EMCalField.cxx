#include "MACE/Geometry/Description/EMCalField.hxx"
#include "MACE/Geometry/Entity/Fast/EMCalField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Geometry::Entity::Fast {

using namespace MACE::PhysicalConstant;

void EMCalField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::EMCalField::Instance();
    auto name = description.GetName();
    auto radius = description.Radius();
    auto length = description.Length();
    auto transform = description.CalcTransform();

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
