#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCLayer.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void CDCLayer::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCLayer";
    const auto detail = description.LayerGeometryDetail();
    const auto count = detail.size();

    for (std::size_t layerID = 0; layerID < count; ++layerID) {
        const auto& [radius, thick, halfLength, _] = detail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            radius - thick / 2,
            radius + thick / 2,
            halfLength,
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
            Mother()->LogicalVolume(),
            false,
            layerID,
            checkOverlaps);
    }
}

} // namespace MACE::Core::Geometry::Entity::Fast
