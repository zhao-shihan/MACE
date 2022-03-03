#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerReadoutLayers::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerReadoutLayers::Instance();
    const auto name = description.GetName();
    const auto thick = description.GetThickness();
    const auto infoList = description.GetInformationList();
    const auto count = infoList.size();

    const auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_He");

    for (size_t layerID = 0; layerID < count; ++layerID) {
        const auto& [radius, halfLength] = infoList[layerID];
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
