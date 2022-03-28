#include "Core/Geometry/Description/SpectrometerSenseWires.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerSenseWires.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Geometry::Entity::Fast::SpectrometerSenseWires;

void SpectrometerSenseWires::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerSenseWires::Instance();
    const auto name = description.GetName();
    const auto rSenseWire = description.GetDiameter() / 2;
    const auto infoList = description.GetInformationList();
    const auto layerCount = infoList.size();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [localPositon, halfLength] = infoList[layerID];
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
