#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSensitiveVolumes.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSensitiveVolumes.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerSensitiveVolumes::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerSensitiveVolumes::Instance();
    const auto name = description.GetName();
    const auto infoList = description.GetInformationList();
    const auto layerCount = infoList.size();

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [radius, halfLength, localPosition] = infoList[layerID];
        auto solid = Make<G4Tubs>(
            name,
            0,
            radius,
            halfLength,
            0,
            2 * M_PI);
        auto logic = Make<G4LogicalVolume>(
            solid,
            Mother()->GetMaterial(layerID),
            name);
        Make<G4PVPlacement>(
            G4Transform3D(
                G4RotationMatrix(),
                localPosition),
            logic,
            name,
            Mother()->GetLogicalVolume(layerID),
            false,
            0,
            checkOverlaps);
    }
}
