#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCSensitiveVolume.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::CDCSensitiveVolume;

void CDCSensitiveVolume::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCSensitiveVolume";
    const auto detail = description.SensitiveVolumeGeometryDetail();
    const auto layerCount = detail.size();

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [rCenter, thick, halfLength, phiCenter, dPhi] = detail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            rCenter - thick / 2,
            rCenter + thick / 2,
            halfLength,
            phiCenter - dPhi / 2,
            dPhi);
        auto logic = Make<G4LogicalVolume>(
            solid,
            Mother()->GetMaterial(layerID),
            name);
        Make<G4PVPlacement>(
            G4Transform3D(),
            logic,
            name,
            Mother()->GetLogicalVolume(layerID),
            false,
            0,
            checkOverlaps);
    }
}
