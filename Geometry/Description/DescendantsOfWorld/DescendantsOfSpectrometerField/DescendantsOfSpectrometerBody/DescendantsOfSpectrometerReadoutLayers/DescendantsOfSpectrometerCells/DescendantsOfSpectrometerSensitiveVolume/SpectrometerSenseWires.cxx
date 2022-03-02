/* #include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerSenseWires.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"

using namespace MACE::Geometry::Description;

SpectrometerSenseWires& SpectrometerSenseWires::Instance() noexcept {
    static SpectrometerSenseWires instance;
    return instance;
}

std::vector<std::pair<int, G4TwoVector>> SpectrometerSenseWires::GetWireInfoList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto cellWidth = readoutLayersDescription.GetThickness();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();

    std::vector<std::pair<int, G4TwoVector, double, double>> infoList;
    for (size_t layerID = 0; layerID < layerInfoList.size(); ++layerID) {
        const auto layerRadius = layerInfoList[layerID].first;
        const auto layerHalfLength = layerInfoList[layerID].second;
        const int cellCount = 4 * std::lround(M_PI_2 / (2 * std::asin(cellWidth / (2 * layerRadius))));
        const auto cellAngle = 2 * M_PI / cellCount;
        const auto gapAngle = 2 * std::asin(fFieldWireDiameter / (2 * layerRadius));
        const auto cellRadius = std::min(layerRadius * std::sin((cellAngle - gapAngle) / 2), cellWidth / 2);
        for (int k = 0; k < cellCount; ++k) {
            auto cellPhi = k * cellAngle;
            auto cellX = layerRadius * std::cos(cellPhi);
            auto cellY = layerRadius * std::sin(cellPhi);
            auto cellPosition = G4TwoVector(cellX, cellY);
            infoList.emplace_back(layerID, cellPosition, cellRadius, layerHalfLength);
        }
    }
    return infoList;
}
 */