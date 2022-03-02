#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerFieldWires.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerFieldWires.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerFieldWires::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerFieldWires::Instance();
    const auto name = description.GetName();
    const auto rFieldWire = description.GetDiameter() / 2;
    const auto infoList = description.GetInformationList();
    const auto cellCount = infoList.size(); // wireCount == 3 * cellCount

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");

    int currentLayerID = -1;
    G4Tubs* solid = nullptr;
    G4LogicalVolume* logic = nullptr;
    for (size_t cellID = 0; cellID < cellCount; ++cellID) {
        auto&& [layerID, infoSubList] = infoList[cellID];
        // cells in a layer shares the same solid and logical volume, and
        // sensitive volumes in a layer shares the same solid and logical volume
        if (layerID != currentLayerID) {
            currentLayerID = layerID;
            solid = Make<G4Tubs>(
                name,
                0,
                rFieldWire,
                dynamic_cast<const G4Tubs*>(Mother()->GetSolid(cellID))->GetZHalfLength(),
                0,
                2 * M_PI);
            logic = Make<G4LogicalVolume>(
                solid,
                material,
                name);
        }
        for (auto&& [fieldWireID, position] : infoSubList) {
            Make<G4PVPlacement>(
                G4Transform3D(
                    G4RotationMatrix(),
                    position),
                name,
                logic,
                Mother()->GetPhysicalVolume(cellID),
                true,
                fieldWireID,
                checkOverlaps);
        }
    }
}
