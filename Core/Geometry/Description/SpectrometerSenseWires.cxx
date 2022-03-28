#include "Core/Geometry/Description/SpectrometerSenseWires.hxx"
#include "Core/Geometry/Description/SpectrometerSensitiveVolumes.hxx"

using MACE::Geometry::Description::SpectrometerSenseWires;

SpectrometerSenseWires& SpectrometerSenseWires::Instance() noexcept {
    static SpectrometerSenseWires instance;
    return instance;
}

std::vector<std::pair<G4TwoVector, double>> SpectrometerSenseWires::GetInformationList() const {
    const auto& svDescription = SpectrometerSensitiveVolumes::Instance();
    const auto svInfoList = svDescription.GetInformationList();
    const auto layerCount = svInfoList.size();

    std::vector<std::pair<G4TwoVector, double>> localPositionList;
    localPositionList.reserve(layerCount);
    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [svCenterR, _0, halfLength, svCenterPhi, _1] = svInfoList[layerID];
        localPositionList.emplace_back(
            G4TwoVector(
                svCenterR * std::cos(svCenterPhi),
                svCenterR * std::sin(svCenterPhi)),
            halfLength);
    }
    return localPositionList;
}
