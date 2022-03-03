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

std::vector<std::tuple<double, double, G4TwoVector>> SpectrometerSensitiveVolumes::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerThick = readoutLayersDescription.GetThickness();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();
    const auto layerCount = layerInfoList.size();

    const auto& cellsDescription = SpectrometerCells::Instance();
    const auto cellInfoList = cellsDescription.GetInformationList();

    const auto& fieldWiresDescription = SpectrometerFieldWires::Instance();
    const auto dFieldWire = fieldWiresDescription.GetDiameter();

    std::vector<std::tuple<double, double, G4TwoVector>> infoList(0);
    infoList.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [cellAngle, halfLength, _] = cellInfoList[layerID];
        const auto svRho = layerInfoList[layerID].first - dFieldWire / 2;
        const auto fieldWireAngle = 2 * std::atan(dFieldWire / (2 * svRho));

        const auto svRadius = std::min(svRho * std::tan((cellAngle - fieldWireAngle) / 2), (layerThick - dFieldWire) / 2);

        const auto svPhi = -fieldWireAngle / 2;
        const auto svX = svRho * std::cos(svPhi);
        const auto svY = svRho * std::sin(svPhi);

        infoList.emplace_back(svRadius, halfLength, G4TwoVector(svX, svY));
    }

    return infoList;
}
