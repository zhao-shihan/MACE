#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/SpectrometerCells.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/DescendantsOfSpectrometerCells/SpectrometerFieldWires.hxx"

using namespace MACE::Geometry::Description;

SpectrometerFieldWires& SpectrometerFieldWires::Instance() noexcept {
    static SpectrometerFieldWires instance;
    return instance;
}

std::vector<std::pair<int, std::array<std::pair<int, G4TwoVector>, 3>>> SpectrometerFieldWires::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerThick = readoutLayersDescription.GetThickness();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();

    const auto& cellsDescription = SpectrometerCells::Instance();
    const auto cellInfoList = cellsDescription.GetInformationList();
    const auto cellCount = cellInfoList.size();

    std::vector<std::pair<int, std::array<std::pair<int, G4TwoVector>, 3>>> infoList(0);
    infoList.reserve(cellCount);

    for (size_t wireID = 0, cellID = 0; cellID < cellCount; ++cellID) {
        auto&& [layerID, cellAngle, cellPhi] = cellInfoList[cellID];
        const auto layerRadius = layerInfoList[layerID].first;

        auto ToXY = [](double rho, double phi)->G4TwoVector {
            return G4TwoVector(
                rho * std::cos(phi),
                rho * std::sin(phi));
        };

        const auto rhoInn = layerRadius - fDiameter / 2;
        const auto rhoOut = rhoInn + layerThick / 2;
        const auto phiLow = cellPhi - std::atan(fDiameter / (2 * rhoInn));
        const auto phiUp = phiLow + cellAngle / 2;

        auto&& infoPair = infoList.emplace_back();
        infoPair.first = layerID;
        auto&& infoSubList = infoPair.second;
        infoSubList[0] = std::make_pair(wireID, ToXY(rhoOut, phiLow) /* + bais[0] */);
        ++wireID;
        infoSubList[1] = std::make_pair(wireID, ToXY(rhoInn, phiUp) /* + bais[1] */);
        ++wireID;
        infoSubList[2] = std::make_pair(wireID, ToXY(rhoOut, phiUp) /* + bais[2] */);
        ++wireID;
    }

    return infoList;
}
