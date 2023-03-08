#include "MACE/Core/Geometry/Description/SpectrometerField.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SpectrometerField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void SpectrometerField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerField::Instance();
    auto name = description.GetName();
    auto length = description.Length();
    auto radius = description.Radius();

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
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
