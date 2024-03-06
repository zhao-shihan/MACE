#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Extension/stdx/ranges_numeric.h++"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Math/Parity.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "Eigen/Geometry"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <tuple>
#include <utility>

namespace MACE::Detector::Description {

using namespace LiteralUnit;
using namespace PhysicalConstant;

CDC::CDC() :
    DescriptionSingletonBase<CDC>("CDC"),
    // Geometry
    fEvenSuperLayerIsAxial{},
    fNSuperLayer{7},
    fNSenseLayerPerSuper{3},
    fGasInnerRadius{15_cm},
    fGasInnerLength{120_cm},
    fEndCapSlope{0.75},
    fMinStereoAngle{6_deg},
    fCellWidthLowerBound{8_mm},
    fReferenceCellWidth{10_mm},
    fCellWidthUpperBound{12_mm},
    fFieldWireDiameter{80_um},
    fSenseWireDiameter{20_um},
    fMinAdjacentSuperLayersDistance{1_mm},
    fMinWireAndRadialShellDistance{2_mm},
    fShellInnerThickness{250_um},
    fShellSideThickness{10_mm},
    fShellOuterThickness{10_mm},
    fCache{},
    // Material
    fButaneFraction{0.15},
    // Detection
    fMeanDriftVelocity{3.5_cm_us},
    fTimeResolutionFWHM{30_ns} {}

auto CDC::GasMaterial() const -> G4Material* {
    constexpr auto materialName{"CDCGas"};
    const auto nist{G4NistManager::Instance()};

    auto gas{nist->FindMaterial(materialName)};
    if (gas) { return gas; }

    const auto heFraction{1 - fButaneFraction};
    const auto he{nist->FindOrBuildMaterial("G4_He")};
    const auto butane{nist->FindOrBuildMaterial("G4_BUTANE")};

    gas = new G4Material{materialName,
                         heFraction * he->GetDensity() + fButaneFraction * butane->GetDensity(),
                         2,
                         kStateGas};
    gas->AddMaterial(he, heFraction);
    gas->AddMaterial(butane, fButaneFraction);

    return gas;
}

auto CDC::ComputeLayerConfiguration() const -> std::vector<SuperLayerConfiguration> {
    std::vector<SuperLayerConfiguration> layerConfig;

    layerConfig.reserve(fNSuperLayer);
    for (int superLayerID{}; superLayerID < fNSuperLayer; ++superLayerID) {
        const auto notFirstSuperLayer{superLayerID > 0};
        auto& super{layerConfig.emplace_back()};
        const auto& lastSuper{notFirstSuperLayer ?
                                  layerConfig[superLayerID - 1] :
                                  layerConfig.front()};

        super.isAxial = fEvenSuperLayerIsAxial ?
                            Math::IsEven(superLayerID) :
                            Math::IsOdd(superLayerID);
        super.superLayerID = superLayerID;
        super.innerRadius = superLayerID > 0 ?
                                lastSuper.outerRadius + fMinAdjacentSuperLayersDistance :
                                fGasInnerRadius + fMinWireAndRadialShellDistance;
        super.nCellPerSenseLayer =
            4 * std::lround(0.5_pi / [this, &super] {
                return std::clamp(
                    fReferenceCellWidth /
                        (fGasInnerRadius + fMinWireAndRadialShellDistance +
                         0.5 * (fNSuperLayer * fNSenseLayerPerSuper * fReferenceCellWidth +
                                (fNSuperLayer - 1) * fMinAdjacentSuperLayersDistance)),
                    fCellWidthLowerBound /
                        (super.innerRadius + fReferenceCellWidth / 2),
                    fCellWidthUpperBound /
                        (super.innerRadius + fNSenseLayerPerSuper * fReferenceCellWidth - fReferenceCellWidth / 2));
            }());
        super.cellAzimuthWidth = 2_pi / super.nCellPerSenseLayer;
        const auto halfPhiCell{super.cellAzimuthWidth / 2};

        super.innerHalfLength =
            notFirstSuperLayer ?
                lastSuper.outerHalfLength + fEndCapSlope * fMinAdjacentSuperLayersDistance :
                fGasInnerLength / 2 + fEndCapSlope * fMinWireAndRadialShellDistance;

        const auto firstInnerStereoZenithAngle{
            [this,
             isAxial{super.isAxial},
             superLayerID] {
                if (isAxial) { return 0.0; }
                if ((fEvenSuperLayerIsAxial ? superLayerID + 3 : superLayerID) % 4 == 0) {
                    return +fMinStereoAngle;
                } else {
                    return -fMinStereoAngle;
                }
            }()};
        const auto firstSenseLayerID{static_cast<int>(superLayerID * fNSenseLayerPerSuper)};
        super.sense.reserve(fNSenseLayerPerSuper);
        for (int senseLayerLocalID{}; senseLayerLocalID < fNSenseLayerPerSuper; ++senseLayerLocalID) {
            const auto notFirstSenseLayerOfThisSuperLayer{senseLayerLocalID > 0};
            auto& sense{super.sense.emplace_back()};
            const auto& lastSense{notFirstSenseLayerOfThisSuperLayer ?
                                      super.sense[senseLayerLocalID - 1] :
                                      super.sense.front()};

            sense.senseLayerID = firstSenseLayerID + senseLayerLocalID;
            sense.innerRadius =
                notFirstSenseLayerOfThisSuperLayer ?
                    lastSense.outerRadius :
                    super.innerRadius;
            sense.outerRadius =
                [rIn{sense.innerRadius},
                 dFW{fFieldWireDiameter},
                 halfPhiCell] {
                    return (rIn + (rIn + dFW) * halfPhiCell) / (1 - halfPhiCell);
                }();
            sense.cellWidth = sense.outerRadius - sense.innerRadius;
            const auto tanInnerStereoZenithAngle{notFirstSenseLayerOfThisSuperLayer ?
                                                     lastSense.TanStereoZenithAngle(lastSense.outerRadius) :
                                                     std::tan(firstInnerStereoZenithAngle)};
            sense.halfLength =
                [eta{fEndCapSlope},
                 lastHL{notFirstSenseLayerOfThisSuperLayer ?
                            lastSense.halfLength :
                            super.innerHalfLength},
                 rIn{sense.innerRadius},
                 lastRIn{notFirstSenseLayerOfThisSuperLayer ?
                             lastSense.innerRadius / std::cos(lastSense.stereoAzimuthAngle / 2) :
                             super.innerRadius},
                 tan2ThetaS{Math::Pow<2>(tanInnerStereoZenithAngle)}] {
                    return (lastHL +
                            eta * (std::sqrt(
                                       Math::Pow<2>(rIn) +
                                       (lastHL + eta * (rIn - lastRIn)) * (lastHL - eta * (rIn + lastRIn)) * tan2ThetaS) -
                                   lastRIn)) /
                           (1 - Math::Pow<2>(eta) * tan2ThetaS);
                }();
            sense.stereoAzimuthAngle = 2 * std::atan(sense.halfLength / sense.innerRadius * tanInnerStereoZenithAngle);

            const auto firstCellID{static_cast<int>((notFirstSuperLayer ?
                                                         lastSuper.sense.back().cell.back().cellID + 1 :
                                                         0) +
                                                    senseLayerLocalID * super.nCellPerSenseLayer)};
            const auto firstCellAzimuth{Math::IsEven(sense.senseLayerID) ?
                                            0 :
                                            halfPhiCell};
            sense.cell.reserve(super.nCellPerSenseLayer);
            for (int cellLocalID{}; cellLocalID < super.nCellPerSenseLayer; ++cellLocalID) {
                auto& cell{sense.cell.emplace_back()};
                cell.cellID = firstCellID + cellLocalID;
                cell.centerAzimuth = firstCellAzimuth + cellLocalID * super.cellAzimuthWidth;
            }
            sense.cell.shrink_to_fit();
        }
        super.sense.shrink_to_fit();

        super.outerRadius =
            [dFW{fFieldWireDiameter},
             &lastSense = std::as_const(super).sense.back()] {
                return (lastSense.outerRadius + dFW) / std::cos(lastSense.stereoAzimuthAngle / 2);
            }();
        super.outerHalfLength = super.innerHalfLength + fEndCapSlope * (super.outerRadius - super.innerRadius);
    }
    layerConfig.shrink_to_fit();

    return layerConfig;
}

auto CDC::ComputeCellMap() const -> std::vector<CellInformation> {
    std::vector<CellInformation> cellMap;

    const auto rFieldWire{fFieldWireDiameter / 2};

    const auto& layerConfig{LayerConfiguration()};
    cellMap.reserve(stdx::ranges::transform_reduce(layerConfig, 0ull, std::plus{},
                                                   [this](const auto& super) {
                                                       return super.nCellPerSenseLayer * fNSenseLayerPerSuper;
                                                   }));

    for (int superLayerID{};
         auto&& super : layerConfig) {
        for (int senseLayerLocalID{};
             auto&& sense : super.sense) {
            const auto wireRadialPosition{Math::MidPoint(sense.innerRadius, sense.outerRadius) + rFieldWire}; // clang-format off
            const Eigen::AngleAxisd stereoRotation{-sense.StereoZenithAngle(wireRadialPosition), Eigen::Vector3d{1, 0, 0}};
            for (int cellLocalID{};
                 auto&& cell : sense.cell) {
                cellMap.push_back({cell.cellID,
                                   cellLocalID,
                                   sense.senseLayerID,
                                   senseLayerLocalID,
                                   superLayerID,
                                   Eigen::Rotation2Dd{cell.centerAzimuth} *
                                       Eigen::Vector2d{wireRadialPosition, 0},
                                   Eigen::AngleAxisd{cell.centerAzimuth, Eigen::Vector3d{0, 0, 1}} *
                                       (stereoRotation * Eigen::Vector3d{0, 0, 1})}); // clang-format on
                // const auto& x0 = cellMap.back().position;
                // const auto& t0 = cellMap.back().direction;
                // const auto& l0 = 2 * sense.halfLength * sense.SecStereoZenithAngle(sense.innerRadius + sense.cellWidth / 2 + fFieldWireDiameter / 2);
                // const auto oldCoutPrecision = std::cout.precision(std::numeric_limits<double>::max_digits10);
                // std::cout << x0.x() << '\t' << x0.y() << '\t' << t0.x() << '\t' << t0.y() << '\t' << t0.z() << '\t' << l0 << std::endl;
                // std::cout.precision(oldCoutPrecision);
                ++cellLocalID;
            }
            ++senseLayerLocalID;
        }
        ++superLayerID;
    }
    cellMap.shrink_to_fit();

    return cellMap;
}

auto CDC::ComputeCellMapFromSenseLayerIDAndLocalCellID() const -> CellMapFromSenseLayerIDAndLocalCellIDType {
    CellMapFromSenseLayerIDAndLocalCellIDType cellMapFromSenseLayerIDAndLocalCellID;
    const auto& cellMap{CellMap()};
    cellMapFromSenseLayerIDAndLocalCellID.reserve(cellMap.size());
    for (auto&& cellInfo : cellMap) {
        cellMapFromSenseLayerIDAndLocalCellID[{cellInfo.senseLayerID, cellInfo.cellLocalID}] = cellInfo;
    }
    return cellMapFromSenseLayerIDAndLocalCellID;
}

auto CDC::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fEvenSuperLayerIsAxial, "EvenSuperLayerIsAxial");
    ImportValue(node, fNSuperLayer, "NSuperLayer");
    ImportValue(node, fNSenseLayerPerSuper, "NSenseLayerPerSuper");
    ImportValue(node, fGasInnerRadius, "GasInnerRadius");
    ImportValue(node, fGasInnerLength, "GasInnerLength");
    ImportValue(node, fEndCapSlope, "EndCapSlope");
    ImportValue(node, fMinStereoAngle, "MinStereoAngle");
    ImportValue(node, fCellWidthLowerBound, "CellWidthLowerBound");
    ImportValue(node, fReferenceCellWidth, "ReferenceCellWidth");
    ImportValue(node, fCellWidthUpperBound, "CellWidthUpperBound");
    ImportValue(node, fFieldWireDiameter, "FieldWireDiameter");
    ImportValue(node, fSenseWireDiameter, "SenseWireDiameter");
    ImportValue(node, fMinAdjacentSuperLayersDistance, "MinAdjacentSuperLayersDistance");
    ImportValue(node, fMinWireAndRadialShellDistance, "MinWireAndRadialShellDistance");
    ImportValue(node, fShellInnerThickness, "ShellInnerThickness");
    ImportValue(node, fShellSideThickness, "ShellSideThickness");
    ImportValue(node, fShellOuterThickness, "ShellOuterThickness");
    // Material
    ImportValue(node, fButaneFraction, "ButaneFraction");
    // Detection
    ImportValue(node, fMeanDriftVelocity, "MeanDriftVelocity");
    ImportValue(node, fTimeResolutionFWHM, "TimeResolutionFWHM");

    fCache.Expire();
}

auto CDC::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fEvenSuperLayerIsAxial, "EvenSuperLayerIsAxial");
    ExportValue(node, fNSuperLayer, "NSuperLayer");
    ExportValue(node, fNSenseLayerPerSuper, "NSenseLayerPerSuper");
    ExportValue(node, fGasInnerRadius, "GasInnerRadius");
    ExportValue(node, fGasInnerLength, "GasInnerLength");
    ExportValue(node, fEndCapSlope, "EndCapSlope");
    ExportValue(node, fMinStereoAngle, "MinStereoAngle");
    ExportValue(node, fCellWidthLowerBound, "CellWidthLowerBound");
    ExportValue(node, fReferenceCellWidth, "ReferenceCellWidth");
    ExportValue(node, fCellWidthUpperBound, "CellWidthUpperBound");
    ExportValue(node, fFieldWireDiameter, "FieldWireDiameter");
    ExportValue(node, fSenseWireDiameter, "SenseWireDiameter");
    ExportValue(node, fMinAdjacentSuperLayersDistance, "MinAdjacentSuperLayersDistance");
    ExportValue(node, fMinWireAndRadialShellDistance, "MinWireAndRadialShellDistance");
    ExportValue(node, fShellInnerThickness, "ShellInnerThickness");
    ExportValue(node, fShellSideThickness, "ShellSideThickness");
    ExportValue(node, fShellOuterThickness, "ShellOuterThickness");
    // Material
    ExportValue(node, fButaneFraction, "ButaneFraction");
    // Detection
    ExportValue(node, fMeanDriftVelocity, "MeanDriftVelocity");
    ExportValue(node, fTimeResolutionFWHM, "TimeResolutionFWHM");
}

} // namespace MACE::Detector::Description
