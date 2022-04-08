#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCCell.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

void CDCCell::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCCell";
    const auto layerDetail = description.LayerGeometryDetail();
    const auto cellDetail = description.CellGeometryDetail();
    const auto layerCount = layerDetail.size();

    for (size_t cellID = 0, layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [cellRadius, cellWidth, halfLength, _0] = layerDetail[layerID];
        auto&& [cellAngle, _1, rotations] = cellDetail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            cellRadius - cellWidth / 2,
            cellRadius + cellWidth / 2,
            halfLength,
            0,
            cellAngle);
        auto logic = Make<G4LogicalVolume>(
            solid,
            Mother()->GetMaterial(layerID),
            name);
        for (auto&& rotation : rotations) {
            Make<G4PVPlacement>(
                G4Transform3D(
                    rotation,
                    G4ThreeVector()),
                logic,
                name,
                Mother()->GetLogicalVolume(layerID),
                false,
                cellID,
                checkOverlaps);
            ++cellID;
        }
    }
}

} // namespace MACE::Core::Geometry::Entity::Fast
