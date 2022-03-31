#include "Core/Geometry/Description/SpectrometerCells.hxx"
#include "Core/Geometry/Description/SpectrometerFieldWires.hxx"
#include "Core/Geometry/Description/SpectrometerReadoutLayers.hxx"

using MACE::Core::Geometry::Description::SpectrometerFieldWires;

SpectrometerFieldWires& SpectrometerFieldWires::Instance() noexcept {
    static SpectrometerFieldWires instance;
    return instance;
}

std::vector<std::pair<double, std::array<G4TwoVector, 3>>> SpectrometerFieldWires::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();
    const auto layerCount = layerInfoList.size();

    const auto& cellsDescription = SpectrometerCells::Instance();
    const auto cellInfoList = cellsDescription.GetInformationList();

    std::vector<std::pair<double, std::array<G4TwoVector, 3>>> infoList(0);
    infoList.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [cellAngle, halfLength, _0] = cellInfoList[layerID];
        const auto& [layerRadius, layerThick, _1, _2] = layerInfoList[layerID];

        auto ToXY = [](double rho, double phi) -> G4TwoVector {
            return G4TwoVector(
                rho * std::cos(phi),
                rho * std::sin(phi));
        };

        const auto rhoInn = layerRadius - fDiameter / 2;
        const auto rhoOut = rhoInn + layerThick / 2;
        const auto phiLow = cellAngle / 2 - std::asin(fDiameter / (2 * rhoInn));
        const auto phiUp = phiLow + cellAngle / 2;

        auto&& infoPair = infoList.emplace_back();
        infoPair.first = halfLength;
        infoPair.second[0] = ToXY(rhoOut, phiLow);
        infoPair.second[1] = ToXY(rhoInn, phiUp);
        infoPair.second[2] = ToXY(rhoOut, phiUp);
    }

    return infoList;
}
