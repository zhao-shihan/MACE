#include "Core/Geometry/Description/SpectrometerFieldWires.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerFieldWires.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::SpectrometerFieldWires;

void SpectrometerFieldWires::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerFieldWires::Instance();
    const auto name = description.GetName();
    const auto rFieldWire = description.GetDiameter() / 2;
    const auto infoList = description.GetInformationList();
    const auto layerCount = infoList.size();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [halfLength, positionList] = infoList[layerID];
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
