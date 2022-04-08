#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;
using namespace Utility::PhysicalConstant;

CDC& CDC::Instance() noexcept {
    static CDC instance;
    return instance;
}

CDC::CDC() :
    IDescription("CDC"),
    fGasInnerRadius(15_cm),
    fGasOuterRadius(45_cm),
    fGasInnerLength(90_cm),
    fGasOuterLength(180_cm),
    fCellWidth(16.2_mm),
    fCellWidthDistortionAllowed(0.1),
    fFieldWireDiameter(110_um),
    fSenseWireDiameter(25_um),
    fSensitiveVolumeRelativeWidth(0.9),
    fShellInnerThickness(200_um),
    fShellSideThickness(5_mm),
    fShellOuterThickness(10_mm) {}

std::vector<std::pair<Eigen::Vector2d, Eigen::Vector3d>> CDC::SenseWireMap() const {
    const auto cellGeometryDetail = CellGeometryDetail();
    const auto senseWireGeometryDetail = SenseWireGeometryDetail();

    const auto layerCount = cellGeometryDetail.size();

    std::vector<std::pair<Eigen::Vector2d, Eigen::Vector3d>> senseWireMap;
    senseWireMap.reserve(3 * layerCount * layerCount); // just an estimation of cell count (pi*r^2), for optimization.

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& wireLocalPosition = senseWireGeometryDetail[layerID].first;
        for (auto&& rotation : std::get<2>(cellGeometryDetail[layerID])) {
            const auto wirePosition = G4TwoVector(rotation * wireLocalPosition);
            const auto wireDirection = CLHEP::HepZHat;
            senseWireMap.emplace_back(Eigen::Vector2d(wirePosition.x(), wirePosition.y()),
                                      Eigen::Vector3d(wireDirection.x(), wireDirection.y(), wireDirection.z()));
        }
    }

    return senseWireMap;
}

std::vector<std::tuple<double, double, double, int>> CDC::LayerGeometryDetail() const {
    std::vector<std::tuple<double, double, double, int>> layerGeometryDetail;

    const auto sideSlope = (fGasOuterLength / 2 - fGasInnerLength / 2) / (fGasOuterRadius - fGasInnerRadius);

    // first layer parameters
    auto layerInnerRadius = fGasInnerRadius;
    auto trueCellWidth = (1 - fCellWidthDistortionAllowed) * fCellWidth;
    int cellCount = 4 * std::lround(halfpi / (2 * std::asin(trueCellWidth / (2 * layerInnerRadius + trueCellWidth))));
    auto cellAngularWidth = 2 * pi / cellCount;

    while (layerInnerRadius + trueCellWidth < fGasOuterRadius) {
        layerGeometryDetail.emplace_back(
            layerInnerRadius + trueCellWidth / 2, // layer center radius
            trueCellWidth,
            fGasInnerLength / 2 + (layerInnerRadius - fGasInnerRadius) * sideSlope, // layer half length
            cellCount);

        // update layer parameters
        layerInnerRadius += trueCellWidth;
        trueCellWidth = 2 * layerInnerRadius * std::sin(cellAngularWidth / 2) / (1 - std::sin(cellAngularWidth / 2));

        if (trueCellWidth > (1 + fCellWidthDistortionAllowed) * fCellWidth) {
            // a new "big" layer
            trueCellWidth = (1 - fCellWidthDistortionAllowed) * fCellWidth;
            cellCount = 4 * std::lround(halfpi / (2 * std::asin(trueCellWidth / (2 * layerInnerRadius + trueCellWidth))));
            cellAngularWidth = 2 * pi / cellCount;
        }
    }

    return layerGeometryDetail;
}

std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> CDC::CellGeometryDetail() const {
    const auto layerGeometryDetail = LayerGeometryDetail();

    const auto layerCount = layerGeometryDetail.size();

    std::vector<std::tuple<double, double, std::vector<G4RotationMatrix>>> cellGeometryDetail;
    cellGeometryDetail.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [_0, _1, halfLength, cellCount] = layerGeometryDetail[layerID];

        const auto cellDeltaPhi = 2 * pi / cellCount;

        auto&& infoSubList = std::get<2>(cellGeometryDetail.emplace_back(cellDeltaPhi, halfLength, 0));
        infoSubList.reserve(cellCount);

        const auto firstCellPhi = (layerID % 2 == 0) ? 0 : (cellDeltaPhi / 2);
        for (int k = 0; k < cellCount; ++k) {
            const auto cellPhi = firstCellPhi + k * cellDeltaPhi;
            infoSubList.emplace_back(CLHEP::HepZHat, cellPhi);
        }
    }

    return cellGeometryDetail;
}

std::vector<std::pair<double, std::array<G4TwoVector, 3>>> CDC::FieldWireGeometryDetail() const {
    const auto layerGeometryDetail = LayerGeometryDetail();
    const auto cellGeometryDetail = CellGeometryDetail();

    const auto layerCount = layerGeometryDetail.size();

    std::vector<std::pair<double, std::array<G4TwoVector, 3>>> fieldWireGeometryDetail;
    fieldWireGeometryDetail.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [cellAngle, halfLength, _0] = cellGeometryDetail[layerID];
        const auto& [layerRadius, layerThick, _1, _2] = layerGeometryDetail[layerID];

        auto ToXY = [](double rho, double phi) -> G4TwoVector {
            return G4TwoVector(rho * std::cos(phi),
                               rho * std::sin(phi));
        };

        const auto rhoInn = layerRadius - fFieldWireDiameter / 2;
        const auto rhoOut = rhoInn + layerThick / 2;
        const auto phiLow = cellAngle / 2 - std::asin(fFieldWireDiameter / (2 * rhoInn));
        const auto phiUp = phiLow + cellAngle / 2;

        fieldWireGeometryDetail.emplace_back(halfLength,
                                             std::array{ToXY(rhoOut, phiLow),
                                                        ToXY(rhoInn, phiUp),
                                                        ToXY(rhoOut, phiUp)});
    }

    return fieldWireGeometryDetail;
}

std::vector<std::pair<G4TwoVector, double>> CDC::SenseWireGeometryDetail() const {
    const auto svGeometryDetail = SensitiveVolumeGeometryDetail();

    const auto layerCount = svGeometryDetail.size();

    std::vector<std::pair<G4TwoVector, double>> senseWireGeometryDetail;
    senseWireGeometryDetail.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [svCenterR, _0, halfLength, svCenterPhi, _1] = svGeometryDetail[layerID];
        senseWireGeometryDetail.emplace_back(G4TwoVector(svCenterR * std::cos(svCenterPhi),
                                                         svCenterR * std::sin(svCenterPhi)),
                                             halfLength);
    }

    return senseWireGeometryDetail;
}

std::vector<std::tuple<double, double, double, double, double>> CDC::SensitiveVolumeGeometryDetail() const {
    const auto layerGeometryDetail = LayerGeometryDetail();
    const auto cellGeometryDetail = CellGeometryDetail();

    const auto layerCount = layerGeometryDetail.size();

    std::vector<std::tuple<double, double, double, double, double>> svGeometeryDetail(0);
    svGeometeryDetail.reserve(layerCount);

    for (size_t layerID = 0; layerID < layerCount; ++layerID) {
        const auto& [cellAngle, halfLength, _0] = cellGeometryDetail[layerID];
        const auto& [layerRho, layerThick, _1, _2] = layerGeometryDetail[layerID];
        const auto svRho = layerRho - fFieldWireDiameter / 2;
        const auto svThick = fSensitiveVolumeRelativeWidth * layerThick;
        const auto fieldWireAngle = 2 * std::asin(fFieldWireDiameter / (2 * layerRho));
        const auto svDPhi = fSensitiveVolumeRelativeWidth * cellAngle;
        const auto svSPhi = (cellAngle - svDPhi) / 2 - fieldWireAngle / 2;
        svGeometeryDetail.emplace_back(svRho, svThick, halfLength, svSPhi + svDPhi / 2, svDPhi);
    }

    return svGeometeryDetail;
}

void CDC::ReadImpl(const YAML::Node& node) {
    fGasInnerRadius = node["GasInnerRadius"].as<decltype(fGasInnerRadius)>();
    fGasOuterRadius = node["GasOuterRadius"].as<decltype(fGasOuterRadius)>();
    fGasInnerLength = node["GasInnerLength"].as<decltype(fGasInnerLength)>();
    fGasOuterLength = node["GasOuterLength"].as<decltype(fGasOuterLength)>();
    fCellWidth = node["CellWidth"].as<decltype(fCellWidth)>();
    fCellWidthDistortionAllowed = node["CellWidthDistortionAllowed"].as<decltype(fCellWidthDistortionAllowed)>();
    fFieldWireDiameter = node["FieldWireDiameter"].as<decltype(fFieldWireDiameter)>();
    fSenseWireDiameter = node["SenseWireDiameter"].as<decltype(fSenseWireDiameter)>();
    fSensitiveVolumeRelativeWidth = node["SensitiveVolumeRelativeWidth"].as<decltype(fSensitiveVolumeRelativeWidth)>();
    fShellInnerThickness = node["ShellInnerThickness"].as<decltype(fShellInnerThickness)>();
    fShellSideThickness = node["ShellSideThickness"].as<decltype(fShellSideThickness)>();
    fShellOuterThickness = node["ShellOuterThickness"].as<decltype(fShellOuterThickness)>();
}

void CDC::WriteImpl(YAML::Node& node) const {
    node["GasInnerRadius"] = fGasInnerRadius;
    node["GasOuterRadius"] = fGasOuterRadius;
    node["GasInnerLength"] = fGasInnerLength;
    node["GasOuterLength"] = fGasOuterLength;
    node["CellWidth"] = fCellWidth;
    node["CellWidthDistortionAllowed"] = fCellWidthDistortionAllowed;
    node["FieldWireDiameter"] = fFieldWireDiameter;
    node["SenseWireDiameter"] = fSenseWireDiameter;
    node["SensitiveVolumeRelativeWidth"] = fSensitiveVolumeRelativeWidth;
    node["ShellInnerThickness"] = fShellInnerThickness;
    node["ShellSideThickness"] = fShellSideThickness;
    node["ShellOuterThickness"] = fShellOuterThickness;
}

} // namespace MACE::Core::Geometry::Description
