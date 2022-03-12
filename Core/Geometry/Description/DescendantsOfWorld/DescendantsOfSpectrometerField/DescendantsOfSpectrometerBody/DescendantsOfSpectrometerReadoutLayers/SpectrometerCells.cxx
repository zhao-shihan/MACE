#include <cmath>
#include <numbers>

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/SpectrometerCells.hxx"

namespace sn = std::numbers;
using namespace MACE::Geometry::Description;

SpectrometerCells& SpectrometerCells::Instance() noexcept {
    static SpectrometerCells instance;
    return instance;
}

std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> SpectrometerCells::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerThick = readoutLayersDescription.GetThickness();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();
    const auto layerCount = layerInfoList.size();

    std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> infoList(0);
    infoList.reserve(layerCount);

    int cellCount = 1;
    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [layerRadius, halfLength] = layerInfoList[layerID];
        if (2 * sn::pi * layerRadius / cellCount > (1 + fAllowedDistortion) * layerThick) {
            cellCount = 4 * std::lround((sn::pi / 2) * layerRadius / ((1 - fAllowedDistortion) * layerThick));
        }
        const auto cellDeltaPhi = 2 * sn::pi / cellCount;
        const auto firstCellPhi = (layerID % 2 == 0) ? 0 : (cellDeltaPhi / 2);

        auto&& infoSubList = std::get<2>(infoList.emplace_back(cellDeltaPhi, halfLength, 0));
        infoSubList.reserve(cellCount);

        for (int k = 0; k < cellCount; ++k) {
            const auto cellPhi = firstCellPhi + k * cellDeltaPhi;
            infoSubList.emplace_back(CLHEP::HepZHat, cellPhi);
        }
    }

    return infoList;
}
