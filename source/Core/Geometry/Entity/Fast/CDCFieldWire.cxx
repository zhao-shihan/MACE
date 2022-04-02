#include "Core/Geometry/Description/CDC.hxx"
#include "Core/Geometry/Entity/Fast/CDCFieldWire.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::CDCFieldWire;

void CDCFieldWire::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCFieldWire";
    const auto rFieldWire = description.GetFieldWireDiameter() / 2;
    const auto detail = description.FieldWireGeometryDetail();
    const auto layerCount = detail.size();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [halfLength, positionList] = detail[layerID];
        auto solid = Make<G4Tubs>(
            name,
            0,
            rFieldWire,
            halfLength,
            0,
            2 * M_PI);
        auto logic = Make<G4LogicalVolume>(
            solid,
            material,
            name);
        for (size_t wireID = 0; wireID < positionList.size(); ++wireID) {
            Make<G4PVPlacement>(
                G4Transform3D(
                    G4RotationMatrix(),
                    positionList[wireID]),
                logic,
                name,
                Mother()->GetLogicalVolume(layerID),
                false,
                wireID,
                checkOverlaps);
        }
    }
}
