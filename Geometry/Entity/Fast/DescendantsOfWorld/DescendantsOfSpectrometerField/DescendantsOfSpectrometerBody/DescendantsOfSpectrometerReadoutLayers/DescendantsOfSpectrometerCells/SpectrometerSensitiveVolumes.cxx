#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSensitiveVolumes.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSensitiveVolumes.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerSensitiveVolumes::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerSensitiveVolumes::Instance();
    const auto name = description.GetName();
    const auto infoList = description.GetInformationList();
    const auto cellCount = infoList.size(); // sensitiveVolumeCount == cellCount

    for (size_t cellID = 0; cellID < cellCount; ++cellID) {
        auto&& [_, svRadius, svPosition] = infoList[cellID];
        auto solid = Make<G4Tubs>(
            name,
            0,
            svRadius,
            dynamic_cast<const G4Tubs*>(Mother()->GetSolid(cellID))->GetZHalfLength(),
            0,
            2 * M_PI);
        auto logic = Make<G4LogicalVolume>(
            solid,
            Mother()->GetMaterial(cellID),
            name);
        Make<G4PVPlacement>(
            G4Transform3D(
                G4RotationMatrix(),
                svPosition),
            name,
            logic,
            Mother()->GetPhysicalVolume(cellID),
            true,
            cellID,
            checkOverlaps);
    }
}
