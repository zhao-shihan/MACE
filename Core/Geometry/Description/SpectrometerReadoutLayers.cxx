#include "Geometry/Description/SpectrometerBody.hxx"
#include "Geometry/Description/SpectrometerReadoutLayers.hxx"

#include <cmath>
#include <numbers>

namespace sn = std::numbers;
using MACE::Geometry::Description::SpectrometerReadoutLayers;

SpectrometerReadoutLayers& SpectrometerReadoutLayers::Instance() noexcept {
    static SpectrometerReadoutLayers instance;
    return instance;
}

std::vector<std::tuple<double, double, double, int>> SpectrometerReadoutLayers::GetInformationList() const {
    const auto& bodyDescription = SpectrometerBody::Instance();
    const auto gasInnerRadius = bodyDescription.GetGasInnerRadius();
    const auto gasOuterRadius = bodyDescription.GetGasOuterRadius();
    const auto gasInnerLength = bodyDescription.GetGasInnerLength();
    const auto gasOuterLength = bodyDescription.GetGasOuterLength();

    const auto sideSlope = (gasOuterLength / 2 - gasInnerLength / 2) / (gasOuterRadius - gasInnerRadius);

    std::vector<std::tuple<double, double, double, int>> infoList(0);
    // first layer parameters
    auto layerInnerRadius = gasInnerRadius;
    auto trueCellWidth = (1 - fAllowedDistortion) * fCellWidth;
    int cellCount = 4 * std::lround((sn::pi / 2) / (2 * std::asin(trueCellWidth / (2 * layerInnerRadius + trueCellWidth))));
    auto cellAngularWidth = 2 * sn::pi / cellCount;
    while (layerInnerRadius + trueCellWidth < gasOuterRadius) {
        infoList.emplace_back(
            layerInnerRadius + trueCellWidth / 2, // layer center radius
            trueCellWidth,
            gasInnerLength / 2 + (layerInnerRadius - gasInnerRadius) * sideSlope, // layer half length
            cellCount);
        // update layer parameters
        layerInnerRadius += trueCellWidth;
        trueCellWidth = 2 * layerInnerRadius * std::sin(cellAngularWidth / 2) / (1 - std::sin(cellAngularWidth / 2));
        if (trueCellWidth > (1 + fAllowedDistortion) * fCellWidth) {
            // a new "big" layer
            trueCellWidth = (1 - fAllowedDistortion) * fCellWidth;
            cellCount = 4 * std::lround((sn::pi / 2) / (2 * std::asin(trueCellWidth / (2 * layerInnerRadius + trueCellWidth))));
            cellAngularWidth = 2 * sn::pi / cellCount;
        }
    }

    return infoList;
}
