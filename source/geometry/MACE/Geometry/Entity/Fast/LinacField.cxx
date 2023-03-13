#include "MACE/Geometry/Description/LinacField.hxx"
#include "MACE/Geometry/Entity/Fast/LinacField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Geometry::Entity::Fast {

using namespace MACE::PhysicalConstant;

void LinacField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::LinacField::Instance();
    const auto name = description.GetName();
    const auto radius = description.Radius();
    const auto length = description.Length();
    const auto transform = description.CalcTransform();

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
