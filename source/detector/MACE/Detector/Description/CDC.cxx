#include "MACE/Detector/Description/CDC.hxx"
#include "MACE/Math/MidPoint.hxx"
#include "MACE/Math/Parity.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "Eigen/Geometry"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <tuple>
#include <utility>

namespace MACE::Detector::Description {

using namespace LiteralUnit::Angle;
using namespace LiteralUnit::Length;
using namespace LiteralUnit::MathConstant;
using namespace PhysicalConstant;

CDC::CDC() :
    DescriptionSingletonBase<CDC>(__func__),
    fEvenSuperLayerIsAxial(false),
    fNSuperLayer(7),
    fNSenseLayerPerSuper(3),
    fGasInnerRadius(15_cm),
    fGasInnerLength(120_cm),
    fEndCapSlope(0.75),
    fMinStereoAngle(4_deg),
    fMinCellWidth(6_mm),
    fReferenceCellWidth(10_mm),
    fMaxCellWidth(14_mm),
    fFieldWireDiameter(80_um),
    fSenseWireDiameter(20_um),
    fSensitiveWidthFactor(0.975),
    fMinAdjacentSuperLayersDistance(1_mm),
    fMinWireAndRadialShellDistance(2_mm),
    fShellInnerThickness(250_um),
    fShellSideThickness(10_mm),
    fShellOuterThickness(10_mm),
    fLayerConfigurationManager(),
    fCellMapManager() {}

std::vector<CDC::SuperLayerConfiguration> CDC::ComputeLayerConfiguration() const {
    std::vector<SuperLayerConfiguration> layerConfig;

    layerConfig.reserve(fNSuperLayer);
    for (gsl::index superLayerID = 0; superLayerID < fNSuperLayer; ++superLayerID) {
        const auto notFirstSuperLayer = superLayerID > 0;
        auto& super = layerConfig.emplace_back();
        const auto& lastSuper = notFirstSuperLayer ?
                                    layerConfig[superLayerID - 1] :
                                    layerConfig.front();

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
                    fMinCellWidth /
                        (super.innerRadius + fReferenceCellWidth / 2),
                    fMaxCellWidth /
                        (super.innerRadius + fNSenseLayerPerSuper * fReferenceCellWidth - fReferenceCellWidth / 2));
            }());
        super.cellAzimuthWidth = 2_pi / super.nCellPerSenseLayer;
        const auto halfPhiCell = super.cellAzimuthWidth / 2;

        super.innerHalfLength =
            notFirstSuperLayer ?
                lastSuper.outerHalfLength + fEndCapSlope * fMinAdjacentSuperLayersDistance :
                fGasInnerLength / 2 + fEndCapSlope * fMinWireAndRadialShellDistance;

        const auto firstInnerStereoZenithAngle =
            [this,
             &isAxial = super.isAxial,
             &superLayerID] {
                if (isAxial) { return 0.0; }
                if ((fEvenSuperLayerIsAxial ? superLayerID + 3 : superLayerID) % 4 == 0) {
                    return +fMinStereoAngle;
                } else {
                    return -fMinStereoAngle;
                }
            }();
        const int firstSenseLayerID = superLayerID * fNSenseLayerPerSuper;
        super.sense.reserve(fNSenseLayerPerSuper);
        for (gsl::index senseLayerLocalID = 0; senseLayerLocalID < fNSenseLayerPerSuper; ++senseLayerLocalID) {
            const auto notFirstSenseLayerOfThisSuperLayer = senseLayerLocalID > 0;
            auto& sense = super.sense.emplace_back();
            const auto& lastSense = notFirstSenseLayerOfThisSuperLayer ?
                                        super.sense[senseLayerLocalID - 1] :
                                        super.sense.front();

            sense.senseLayerID = firstSenseLayerID + senseLayerLocalID;
            sense.innerRadius =
                notFirstSenseLayerOfThisSuperLayer ?
                    lastSense.outerRadius :
                    super.innerRadius;
            sense.outerRadius =
                [&rIn = std::as_const(sense).innerRadius,
                 &dFW = fFieldWireDiameter,
                 &halfPhiCell] {
                    return (rIn + (rIn + dFW) * halfPhiCell) / (1 - halfPhiCell);
                }();
            sense.cellWidth = sense.outerRadius - sense.innerRadius;
            const auto tanInnerStereoZenithAngle = notFirstSenseLayerOfThisSuperLayer ?
                                                       lastSense.TanStereoZenithAngle(lastSense.outerRadius) :
                                                       std::tan(firstInnerStereoZenithAngle);
            sense.halfLength =
                [&eta = fEndCapSlope,
                 &lastHL = notFirstSenseLayerOfThisSuperLayer ?
                               std::as_const(lastSense).halfLength :
                               std::as_const(super).innerHalfLength,
                 &rIn = std::as_const(sense).innerRadius,
                 lastRIn = notFirstSenseLayerOfThisSuperLayer ?
                               lastSense.innerRadius / std::cos(lastSense.stereoAzimuthAngle / 2) :
                               super.innerRadius,
                 tan2ThetaS = Math::Pow2(tanInnerStereoZenithAngle)] {
                    return (lastHL +
                            eta * (std::sqrt(
                                       Math::Pow2(rIn) +
                                       (lastHL + eta * (rIn - lastRIn)) * (lastHL - eta * (rIn + lastRIn)) * tan2ThetaS) -
                                   lastRIn)) /
                           (1 - Math::Pow2(eta) * tan2ThetaS);
                }();
            sense.stereoAzimuthAngle = 2 * std::atan(sense.halfLength / sense.innerRadius * tanInnerStereoZenithAngle);

            const int firstCellID = (notFirstSuperLayer ?
                                         lastSuper.sense.back().cell.back().cellID + 1 :
                                         0) +
                                    senseLayerLocalID * super.nCellPerSenseLayer;
            const auto firstCellAzimuth = Math::IsEven(sense.senseLayerID) ?
                                              0 :
                                              halfPhiCell;
            sense.cell.reserve(super.nCellPerSenseLayer);
            for (gsl::index cellLocalID = 0; cellLocalID < super.nCellPerSenseLayer; ++cellLocalID) {
                auto& cell = sense.cell.emplace_back();
                cell.cellID = firstCellID + cellLocalID;
                cell.centerAzimuth = firstCellAzimuth + cellLocalID * super.cellAzimuthWidth;
            }
            sense.cell.shrink_to_fit();
        }
        super.sense.shrink_to_fit();

        super.outerRadius =
            [&dFW = fFieldWireDiameter,
             &lastSense = std::as_const(super).sense.back()] {
                return lastSense.outerRadius / std::cos(lastSense.stereoAzimuthAngle / 2) + dFW;
            }();
        super.outerHalfLength = super.innerHalfLength + fEndCapSlope * (super.outerRadius - super.innerRadius);
    }
    layerConfig.shrink_to_fit();

    return layerConfig;
}

std::vector<CDC::CellInformation> CDC::ComputeCellMap() const {
    std::vector<CellInformation> cellMap;

    const auto rFieldWire = fFieldWireDiameter / 2;

    const auto& layerConfig = LayerConfiguration();
    cellMap.reserve(
        std::accumulate(layerConfig.cbegin(), layerConfig.cend(), 0,
                        [this](const auto& count, const auto& super) {
                            return count + super.nCellPerSenseLayer * fNSenseLayerPerSuper;
                        }));

    for (auto superLayerID = 0;
         auto&& super : layerConfig) {
        for (auto senseLayerLocalID = 0;
             auto&& sense : super.sense) {
            const auto wireRadialPosition = Math::MidPoint(sense.innerRadius, sense.outerRadius) + rFieldWire;
            const Eigen::AngleAxisd stereoRotation = {-sense.StereoZenithAngle(wireRadialPosition), Eigen::Vector3d(1, 0, 0)};
            for (auto cellLocalID = 0;
                 auto&& cell : sense.cell) {
                cellMap.push_back({cellLocalID,
                                   sense.senseLayerID,
                                   senseLayerLocalID,
                                   superLayerID,
                                   Eigen::Rotation2Dd(cell.centerAzimuth) *
                                       Eigen::Vector2d(wireRadialPosition, 0),
                                   Eigen::AngleAxisd(cell.centerAzimuth, Eigen::Vector3d(0, 0, 1)) *
                                       (stereoRotation * Eigen::Vector3d(0, 0, 1))});
                ++cellLocalID;
            }
            ++senseLayerLocalID;
        }
        ++superLayerID;
    }
    cellMap.shrink_to_fit();

    return cellMap;
}

void CDC::ImportValues(const YAML::Node& node) {
    ImportValue(node, fEvenSuperLayerIsAxial, "EvenSuperLayerIsAxial");
    ImportValue(node, fNSuperLayer, "NSuperLayer");
    ImportValue(node, fNSenseLayerPerSuper, "NSenseLayerPerSuper");
    ImportValue(node, fGasInnerRadius, "GasInnerRadius");
    ImportValue(node, fGasInnerLength, "GasInnerLength");
    ImportValue(node, fEndCapSlope, "EndCapSlope");
    ImportValue(node, fMinStereoAngle, "MinStereoAngle");
    ImportValue(node, fMinCellWidth, "MinCellWidth");
    ImportValue(node, fReferenceCellWidth, "ReferenceCellWidth");
    ImportValue(node, fMaxCellWidth, "MaxCellWidth");
    ImportValue(node, fFieldWireDiameter, "FieldWireDiameter");
    ImportValue(node, fSenseWireDiameter, "SenseWireDiameter");
    ImportValue(node, fSensitiveWidthFactor, "SensitiveWidthFactor");
    ImportValue(node, fMinAdjacentSuperLayersDistance, "MinAdjacentSuperLayersDistance");
    ImportValue(node, fMinWireAndRadialShellDistance, "MinWireAndRadialShellDistance");
    ImportValue(node, fShellInnerThickness, "ShellInnerThickness");
    ImportValue(node, fShellSideThickness, "ShellSideThickness");
    ImportValue(node, fShellOuterThickness, "ShellOuterThickness");
}

void CDC::ExportValues(YAML::Node& node) const {
    ExportValue(node, fEvenSuperLayerIsAxial, "EvenSuperLayerIsAxial");
    ExportValue(node, fNSuperLayer, "NSuperLayer");
    ExportValue(node, fNSenseLayerPerSuper, "NSenseLayerPerSuper");
    ExportValue(node, fGasInnerRadius, "GasInnerRadius");
    ExportValue(node, fGasInnerLength, "GasInnerLength");
    ExportValue(node, fEndCapSlope, "EndCapSlope");
    ExportValue(node, fMinStereoAngle, "MinStereoAngle");
    ExportValue(node, fMinCellWidth, "MinCellWidth");
    ExportValue(node, fReferenceCellWidth, "ReferenceCellWidth");
    ExportValue(node, fMaxCellWidth, "MaxCellWidth");
    ExportValue(node, fFieldWireDiameter, "FieldWireDiameter");
    ExportValue(node, fSenseWireDiameter, "SenseWireDiameter");
    ExportValue(node, fSensitiveWidthFactor, "SensitiveWidthFactor");
    ExportValue(node, fMinAdjacentSuperLayersDistance, "MinAdjacentSuperLayersDistance");
    ExportValue(node, fMinWireAndRadialShellDistance, "MinWireAndRadialShellDistance");
    ExportValue(node, fShellInnerThickness, "ShellInnerThickness");
    ExportValue(node, fShellSideThickness, "ShellSideThickness");
    ExportValue(node, fShellOuterThickness, "ShellOuterThickness");
}

} // namespace MACE::Detector::Description
