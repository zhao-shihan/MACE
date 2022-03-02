#include <cmath>

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/SpectrometerCells.hxx"

using namespace MACE::Geometry::Description;

SpectrometerCells& SpectrometerCells::Instance() noexcept {
    static SpectrometerCells instance;
    return instance;
}

std::vector<std::tuple<int, double, double>> SpectrometerCells::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerThick = readoutLayersDescription.GetThickness();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();
    const auto layerCount = layerInfoList.size();

    std::vector<std::tuple<int, double, double>> infoList(0);
    infoList.reserve(layerCount * layerCount); // an estimation for performance optimization

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& layerRadius = layerInfoList[layerID].first;
        const auto cellCount = 4 * std::lround(M_PI_2 / (2 * std::asin(layerThick / (2 * layerRadius))));
        const auto cellDeltaPhi = 2 * M_PI / cellCount;
        const auto firstCellPhi = (layerID % 2 == 0) ? 0 : (cellDeltaPhi / 2);
        for (int k = 0; k < cellCount; ++k) {
            const auto cellPhi = firstCellPhi + k * cellDeltaPhi;
            infoList.emplace_back(layerID, cellDeltaPhi, cellPhi);
        }
    }

    return infoList;
}
