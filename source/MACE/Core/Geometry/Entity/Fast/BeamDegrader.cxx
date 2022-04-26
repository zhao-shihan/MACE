#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Entity/Fast/BeamDegrader.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::LiteralUnit::Density;

void BeamDegrader::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::BeamDegrader::Instance();
    const auto name = description.GetName();
    const auto width = description.GetWidth();
    const auto thickness = description.GetThickness();
    const auto transform = description.CalcTransform();

    auto solid = Make<G4Box>(
        name,
        width / 2,
        width / 2,
        thickness / 2);
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
