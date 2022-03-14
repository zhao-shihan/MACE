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

std::vector<std::tuple<double, double, double, double, double>> SpectrometerSensitiveVolumes::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerThick = readoutLayersDescription.GetThickness();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();
    const auto layerCount = layerInfoList.size();

    const auto& cellsDescription = SpectrometerCells::Instance();
    const auto cellInfoList = cellsDescription.GetInformationList();

    const auto& fieldWiresDescription = SpectrometerFieldWires::Instance();
    const auto dFieldWire = fieldWiresDescription.GetDiameter();

    std::vector<std::tuple<double, double, double, double, double>> infoList(0);
    infoList.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [cellAngle, halfLength, _] = cellInfoList[layerID];
        const auto layerRho = layerInfoList[layerID].first;
        const auto svRho = layerRho - dFieldWire / 2;
        const auto svThick = fSensitiveWidth * layerThick;
        const auto fieldWireAngle = 2 * std::asin(dFieldWire / (2 * layerRho));
        const auto svDPhi = fSensitiveWidth * cellAngle;
        const auto svSPhi = (cellAngle - svDPhi) / 2 - fieldWireAngle / 2;
        infoList.emplace_back(svRho, svThick, halfLength, svSPhi + svDPhi / 2, svDPhi);
    }

    return infoList;
}
