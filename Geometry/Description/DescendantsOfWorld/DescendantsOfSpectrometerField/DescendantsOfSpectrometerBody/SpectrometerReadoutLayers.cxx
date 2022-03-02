#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"

using namespace MACE::Geometry::Description;

SpectrometerReadoutLayers& SpectrometerReadoutLayers::Instance() noexcept {
    static SpectrometerReadoutLayers instance;
    return instance;
}

std::vector<std::pair<double, double>> SpectrometerReadoutLayers::GetInformationList() const {
    const auto& bodyDescription = SpectrometerBody::Instance();
    const auto gasInnerRadius = bodyDescription.GetGasInnerRadius();
    const auto gasOuterRadius = bodyDescription.GetGasOuterRadius();
    const auto gasInnerLength = bodyDescription.GetGasInnerLength();
    const auto gasOuterLength = bodyDescription.GetGasOuterLength();

    const auto sideSlope = (gasOuterLength / 2 - gasInnerLength / 2) / (gasOuterRadius - gasInnerRadius);
    const auto layerCount = static_cast<int>((gasOuterRadius - gasInnerRadius) / fLayerThickness);

    std::vector<std::pair<double, double>> infoList(0);
    for (int i = 0; i < layerCount; ++i) {
        const auto layerCenterRadius = gasInnerRadius + (i + 0.5) * fLayerThickness;
        const auto halfLength = gasInnerLength / 2 + i * fLayerThickness * sideSlope;
        infoList.emplace_back(layerCenterRadius, halfLength);
    }

    return infoList;
}
