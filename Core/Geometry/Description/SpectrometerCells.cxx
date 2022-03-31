#include "Core/Geometry/Description/SpectrometerCells.hxx"
#include "Core/Geometry/Description/SpectrometerReadoutLayers.hxx"
#include "Utility/PhysicalConstant.hxx"

#include <cmath>

namespace MACE::Core::Geometry::Description {

using namespace Utility::PhysicalConstant;

SpectrometerCells& SpectrometerCells::Instance() noexcept {
    static SpectrometerCells instance;
    return instance;
}

SpectrometerCells::SpectrometerCells() :
    IDescription("SpectrometerCells") {}

std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> SpectrometerCells::GetInformationList() const {
    const auto& readoutLayersDescription = SpectrometerReadoutLayers::Instance();
    const auto layerInfoList = readoutLayersDescription.GetInformationList();
    const auto layerCount = layerInfoList.size();

    std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> infoList(0);
    infoList.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [_0, _1, halfLength, cellCount] = layerInfoList[layerID];

        const auto cellDeltaPhi = 2 * pi / cellCount;

        auto&& infoSubList = std::get<2>(infoList.emplace_back(cellDeltaPhi, halfLength, 0));
        infoSubList.reserve(cellCount);

        const auto firstCellPhi = (layerID % 2 == 0) ? 0 : (cellDeltaPhi / 2);
        for (int k = 0; k < cellCount; ++k) {
            const auto cellPhi = firstCellPhi + k * cellDeltaPhi;
            infoSubList.emplace_back(CLHEP::HepZHat, cellPhi);
        }
    }

    return infoList;
}

} // namespace MACE::Core::Geometry::Description
