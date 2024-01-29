#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Math/IntegerPower.h++"

#include "Eigen/Core"

#include "gsl/gsl"

#include <vector>

namespace MACE::Detector::Description {

class CDC final : public DescriptionSingletonBase<CDC> {
    friend Env::Memory::SingletonInstantiator;

private:
    CDC();
    ~CDC() = default;

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    auto EvenSuperLayerIsAxial() const -> auto { return fEvenSuperLayerIsAxial; }
    auto NSuperLayer() const -> auto { return fNSuperLayer; }
    auto NSenseLayerPerSuper() const -> auto { return fNSenseLayerPerSuper; }
    auto GasInnerRadius() const -> auto { return fGasInnerRadius; }
    auto GasInnerLength() const -> auto { return fGasInnerLength; }
    auto EndCapSlope() const -> auto { return fEndCapSlope; }
    auto MinStereoAngle() const -> auto { return fMinStereoAngle; }
    auto MinCellWidth() const -> auto { return fMinCellWidth; }
    auto ReferenceCellWidth() const -> auto { return fReferenceCellWidth; }
    auto MaxCellWidth() const -> auto { return fMaxCellWidth; }
    auto FieldWireDiameter() const -> auto { return fFieldWireDiameter; }
    auto SenseWireDiameter() const -> auto { return fSenseWireDiameter; }
    auto SensitiveWidthFactor() const -> auto { return fSensitiveWidthFactor; }
    auto MinAdjacentSuperLayersDistance() const -> auto { return fMinAdjacentSuperLayersDistance; }
    auto MinWireAndRadialShellDistance() const -> auto { return fMinWireAndRadialShellDistance; }
    auto ShellInnerThickness() const -> auto { return fShellInnerThickness; }
    auto ShellSideThickness() const -> auto { return fShellSideThickness; }
    auto ShellOuterThickness() const -> auto { return fShellOuterThickness; }

    auto EvenSuperLayerIsAxial(bool v) -> void { fEvenSuperLayerIsAxial = v, SetGeometryOutdated(); }
    auto NSuperLayer(int v) -> void { fNSuperLayer = v, SetGeometryOutdated(); }
    auto NSenseLayerPerSuper(int v) -> void { fNSenseLayerPerSuper = v, SetGeometryOutdated(); }
    auto GasInnerRadius(double v) -> void { fGasInnerRadius = v, SetGeometryOutdated(); }
    auto GasInnerLength(double v) -> void { fGasInnerLength = v, SetGeometryOutdated(); }
    auto EndCapSlope(double v) -> void { fEndCapSlope = v, SetGeometryOutdated(); }
    auto MinStereoAngle(double v) -> void { fMinStereoAngle = v, SetGeometryOutdated(); }
    auto MinCellWidth(double v) -> void { fMinCellWidth = v, SetGeometryOutdated(); }
    auto ReferenceCellWidth(double v) -> void { fReferenceCellWidth = v, SetGeometryOutdated(); }
    auto MaxCellWidth(double v) -> void { fMaxCellWidth = v, SetGeometryOutdated(); }
    auto FieldWireDiameter(double v) -> void { fFieldWireDiameter = v, SetGeometryOutdated(); }
    auto SenseWireDiameter(double v) -> void { fSenseWireDiameter = v, SetGeometryOutdated(); }
    auto SensitiveWidthFactor(double v) -> void { fSensitiveWidthFactor = v, SetGeometryOutdated(); }
    auto MinAdjacentSuperLayersDistance(double v) -> void { fMinAdjacentSuperLayersDistance = v, SetGeometryOutdated(); }
    auto MinWireAndRadialShellDistance(double v) -> void { fMinWireAndRadialShellDistance = v, SetGeometryOutdated(); }
    auto ShellInnerThickness(double v) -> void { fShellInnerThickness = v, SetGeometryOutdated(); }
    auto ShellSideThickness(double v) -> void { fShellSideThickness = v, SetGeometryOutdated(); }
    auto ShellOuterThickness(double v) -> void { fShellOuterThickness = v, SetGeometryOutdated(); }

    struct SuperLayerConfiguration {
        struct SenseLayerConfiguration {
            struct CellConfiguration {
                int cellID;
                double centerAzimuth;
            };
            int senseLayerID;
            double innerRadius;
            double outerRadius;
            double cellWidth;
            double halfLength;
            double stereoAzimuthAngle;
            auto TanStereoZenithAngle(double r) const -> auto { return r / halfLength * std::tan(stereoAzimuthAngle / 2); }
            auto SecStereoZenithAngle(double r) const -> auto { return std::sqrt(1 + Math::Pow<2>(TanStereoZenithAngle(r))); }
            auto CosStereoZenithAngle(double r) const -> auto { return 1 / SecStereoZenithAngle(r); }
            auto SinStereoZenithAngle(double r) const -> auto { return TanStereoZenithAngle(r) / SecStereoZenithAngle(r); }
            auto StereoZenithAngle(double r) const -> auto { return std::atan(TanStereoZenithAngle(r)); }
            std::vector<CellConfiguration> cell;
        };
        bool isAxial;
        int superLayerID;
        int nCellPerSenseLayer;
        double cellAzimuthWidth;
        double innerRadius;
        double innerHalfLength;
        double outerRadius;
        double outerHalfLength;
        std::vector<SenseLayerConfiguration> sense;
    };

    auto LayerConfiguration() const -> const auto& { return fLayerConfigurationManager.Get(this); }
    auto GasOuterRadius() const -> auto { return LayerConfiguration().back().outerRadius + fMinWireAndRadialShellDistance; }
    auto GasOuterLength() const -> auto { return fGasInnerLength + 2 * fEndCapSlope * (GasOuterRadius() - fGasInnerRadius); }

    struct CellInformation {
        int cellLocalID;
        int senseLayerID;
        int senseLayerLocalID;
        int superLayerID;
        Eigen::Vector2d position;
        Eigen::Vector3d direction;
    };

    auto CellMap() const -> const auto& { return fCellMapManager.Get(this); }

    ///////////////////////////////////////////////////////////
    // Detection
    ///////////////////////////////////////////////////////////

    auto MeanDriftVelocity() const -> auto { return fMeanDriftVelocity; }
    auto TimeResolutionFWHM() const -> auto { return fTimeResolutionFWHM; }

    auto MeanDriftVelocity(double v) -> void { fMeanDriftVelocity = v; }
    auto TimeResolutionFWHM(double v) -> void { fTimeResolutionFWHM = v; }

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    class LayerConfigurationManager {
    public:
        auto SetOutdated() -> void { fOutdated = true; }
        inline auto Get(const CDC* cdc) -> const std::vector<SuperLayerConfiguration>&;

    private:
        bool fOutdated = true;
        std::vector<SuperLayerConfiguration> fLayerConfiguration = {};
    };

    class CellMapManager {
    public:
        auto SetOutdated() -> void { fOutdated = true; }
        inline auto Get(const CDC* cdc) -> const std::vector<CellInformation>&;

    private:
        bool fOutdated = true;
        std::vector<CellInformation> fCellMap = {};
    };

    inline auto SetGeometryOutdated() const -> void;
    auto ComputeLayerConfiguration() const -> std::vector<SuperLayerConfiguration>;
    auto ComputeCellMap() const -> std::vector<CellInformation>;

    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    bool fEvenSuperLayerIsAxial; // true: AVAUAVAU..., false: VAUAVAUA...
    int fNSuperLayer;
    int fNSenseLayerPerSuper;
    double fGasInnerRadius;
    double fGasInnerLength;
    double fEndCapSlope;
    double fMinStereoAngle;
    double fMinCellWidth;
    double fReferenceCellWidth;
    double fMaxCellWidth;
    double fFieldWireDiameter;
    double fSenseWireDiameter;
    double fSensitiveWidthFactor;
    double fMinAdjacentSuperLayersDistance;
    double fMinWireAndRadialShellDistance;
    double fShellInnerThickness;
    double fShellSideThickness;
    double fShellOuterThickness;

    mutable LayerConfigurationManager fLayerConfigurationManager;
    mutable CellMapManager fCellMapManager;

    ///////////////////////////////////////////////////////////
    // Detection
    ///////////////////////////////////////////////////////////

    double fMeanDriftVelocity;
    double fTimeResolutionFWHM;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/CDC.inl"
