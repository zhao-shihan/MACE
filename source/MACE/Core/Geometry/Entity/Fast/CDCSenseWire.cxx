#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCSenseWire.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::CDCSenseWire;

void CDCSenseWire::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCSenseWire";
    const auto rSenseWire = description.GetSenseWireDiameter() / 2;
    const auto detail = description.SenseWireGeometryDetail();
    const auto layerCount = detail.size();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [localPositon, halfLength] = detail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            0,
            rSenseWire,
            halfLength,
            0,
            2 * M_PI);
        auto logic = Make<G4LogicalVolume>(
            solid,
            material,
            name);
        Make<G4PVPlacement>(
            G4Transform3D(
                G4RotationMatrix(),
                localPositon),
            logic,
            name,
            Mother()->GetLogicalVolume(layerID),
            false,
            0,
            checkOverlaps);
    }
}
