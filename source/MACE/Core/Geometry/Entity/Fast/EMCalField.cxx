#include "MACE/Core/Geometry/Description/EMCalField.hxx"
#include "MACE/Core/Geometry/Entity/Fast/EMCalField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void EMCalField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::EMCalField::Instance();
    auto name = description.GetName();
    auto radius = description.GetRadius();
    auto length = description.GetLength();
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
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
