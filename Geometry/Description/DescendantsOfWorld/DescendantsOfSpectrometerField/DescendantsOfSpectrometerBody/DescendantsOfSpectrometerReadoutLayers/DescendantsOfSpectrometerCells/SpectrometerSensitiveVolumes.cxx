#include <cmath>

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/SpectrometerCells.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerFieldWires.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSensitiveVolumes.hxx"

using namespace MACE::Geometry::Description;

SpectrometerSensitiveVolumes& SpectrometerSensitiveVolumes::Instance() noexcept {
    static SpectrometerSensitiveVolumes instance;
    return instance;
}

std::vector<std::tuple<int, double, G4TwoVector>> SpectrometerSensitiveVolumes::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerThick = readoutLayersDescription.GetThickness();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();

    const auto& cellsDescription = SpectrometerCells::Instance();
    const auto cellInfoList = cellsDescription.GetInformationList();
    const auto cellCount = cellInfoList.size();

    const auto& fieldWiresDescription = SpectrometerFieldWires::Instance();
    const auto dFieldWire = fieldWiresDescription.GetDiameter();

    std::vector<std::tuple<int, double, G4TwoVector>> infoList(0);
    infoList.reserve(cellCount);

    for (size_t cellID = 0; cellID < cellCount; ++cellID) {
        auto&& [layerID, cellAngle, cellPhi] = cellInfoList[cellID];
        const auto svRho = layerInfoList[layerID].first - dFieldWire / 2;
        const auto fieldWireAngle = 2 * std::atan(dFieldWire / (2 * svRho));

        const auto svRadius = std::min(svRho * std::tan((cellAngle - fieldWireAngle) / 2), (layerThick - dFieldWire) / 2);

        const auto svPhi = cellPhi - fieldWireAngle / 2;
        const auto svX = svRho * std::cos(svPhi) /* + baisX */;
        const auto svY = svRho * std::sin(svPhi) /* + baisY */;

        infoList.emplace_back(layerID, svRadius, G4TwoVector(svX, svY));
    }

    return infoList;
}
