#include "Core/Geometry/Description/CDC.hxx"
#include "Core/Geometry/Entity/Fast/CDCLayer.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::CDCLayer;

void CDCLayer::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCLayer";
    const auto detail = description.LayerGeometryDetail();
    const auto count = detail.size();

    const auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_He");

    for (size_t layerID = 0; layerID < count; ++layerID) {
        const auto& [radius, thick, halfLength, _] = detail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            radius - thick / 2,
            radius + thick / 2,
            halfLength,
            0,
            2 * M_PI);
        auto logic = Make<G4LogicalVolume>(
            solid,
            material,
            name);
        Make<G4PVPlacement>(
            G4Transform3D(),
            logic,
            name,
            Mother()->GetLogicalVolume(),
            false,
            layerID,
            checkOverlaps);
    }
}
