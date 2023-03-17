#pragma once

#include "MACE/Detector/DescriptionBase.hxx"
#include "MACE/Math/IntegerPower.hxx"

#include "Eigen/Core"

#include "gsl/gsl"

#include <vector>

namespace MACE::Detector::Description {

class CDC final : public DescriptionSingletonBase<CDC> {
    friend Env::Memory::SingletonFactory;

private:
    CDC();

public:
    ///////////////////////////////////////////////////////////
    // Geometry properties
    ///////////////////////////////////////////////////////////

    const auto& EvenSuperLayerIsAxial() const { return fEvenSuperLayerIsAxial; }
    const auto& NSuperLayer() const { return fNSuperLayer; }
    const auto& NSenseLayerPerSuper() const { return fNSenseLayerPerSuper; }
    const auto& GasInnerRadius() const { return fGasInnerRadius; }
    const auto& GasInnerLength() const { return fGasInnerLength; }
    const auto& EndCapSlope() const { return fEndCapSlope; }
    const auto& MinStereoAngle() const { return fMinStereoAngle; }
    const auto& MinCellWidth() const { return fMinCellWidth; }
    const auto& ReferenceCellWidth() const { return fReferenceCellWidth; }
    const auto& MaxCellWidth() const { return fMaxCellWidth; }
    const auto& FieldWireDiameter() const { return fFieldWireDiameter; }
    const auto& SenseWireDiameter() const { return fSenseWireDiameter; }
    const auto& SensitiveWidthFactor() const { return fSensitiveWidthFactor; }
    const auto& MinAdjacentSuperLayersDistance() const { return fMinAdjacentSuperLayersDistance; }
    const auto& MinWireAndRadialShellDistance() const { return fMinWireAndRadialShellDistance; }
    const auto& ShellInnerThickness() const { return fShellInnerThickness; }
    const auto& ShellSideThickness() const { return fShellSideThickness; }
    const auto& ShellOuterThickness() const { return fShellOuterThickness; }

    void EvenSuperLayerIsAxial(auto&& v) { (fEvenSuperLayerIsAxial = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void NSuperLayer(auto&& v) { (fNSuperLayer = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void NSenseLayerPerSuper(auto&& v) { (fNSenseLayerPerSuper = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void GasInnerRadius(auto&& v) { (fGasInnerRadius = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void GasInnerLength(auto&& v) { (fGasInnerLength = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void EndCapSlope(auto&& v) { (fEndCapSlope = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void MinStereoAngle(auto&& v) { (fMinStereoAngle = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void MinCellWidth(auto&& v) { (fMinCellWidth = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void ReferenceCellWidth(auto&& v) { (fReferenceCellWidth = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void MaxCellWidth(auto&& v) { (fMaxCellWidth = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void FieldWireDiameter(auto&& v) { (fFieldWireDiameter = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void SenseWireDiameter(auto&& v) { (fSenseWireDiameter = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void SensitiveWidthFactor(auto&& v) { (fSensitiveWidthFactor = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void MinAdjacentSuperLayersDistance(auto&& v) { (fMinAdjacentSuperLayersDistance = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void MinWireAndRadialShellDistance(auto&& v) { (fMinWireAndRadialShellDistance = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void ShellInnerThickness(auto&& v) { (fShellInnerThickness = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void ShellSideThickness(auto&& v) { (fShellSideThickness = std::forward<decltype(v)>(v), SetGeometryOutdated()); }
    void ShellOuterThickness(auto&& v) { (fShellOuterThickness = std::forward<decltype(v)>(v), SetGeometryOutdated()); }

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
            auto TanStereoZenithAngle(const auto r) const { return r / halfLength * std::tan(stereoAzimuthAngle / 2); }
            auto SecStereoZenithAngle(const auto r) const { return std::sqrt(1 + Math::Pow2(TanStereoZenithAngle(r))); }
            auto CosStereoZenithAngle(const auto r) const { return 1 / SecStereoZenithAngle(r); }
            auto SinStereoZenithAngle(const auto r) const { return TanStereoZenithAngle(r) / SecStereoZenithAngle(r); }
            auto StereoZenithAngle(const auto r) const { return std::atan(TanStereoZenithAngle(r)); }
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

    const auto& LayerConfiguration() const { return fLayerConfigurationManager.Get(this); }
    auto GasOuterRadius() const { return LayerConfiguration().back().outerRadius + fMinWireAndRadialShellDistance; }
    auto GasOuterLength() const { return fGasInnerLength + 2 * fEndCapSlope * (GasOuterRadius() - fGasInnerRadius); }

    struct CellInformation {
        int cellLocalID;
        int senseLayerID;
        int senseLayerLocalID;
        int superLayerID;
        Eigen::Vector2d position;
        Eigen::Vector3d direction;
    };

    const auto& CellMap() const { return fCellMapManager.Get(this); }

    ///////////////////////////////////////////////////////////
    // Detection properties
    ///////////////////////////////////////////////////////////

    const auto& MeanDriftVelocity() const { return fMeanDriftVelocity; }
    const auto& TimeResolution() const { return fTimeResolution; }

    void MeanDriftVelocity(auto&& v) { fMeanDriftVelocity = std::forward<decltype(v)>(v); }
    void TimeResolution(auto&& v) { fTimeResolution = std::forward<decltype(v)>(v); }

private:
    ///////////////////////////////////////////////////////////
    // Geometry properties
    ///////////////////////////////////////////////////////////

    class LayerConfigurationManager {
    public:
        void SetOutdated() { fOutdated = true; }
        inline const std::vector<SuperLayerConfiguration>& Get(const CDC* cdc);

    private:
        bool fOutdated = true;
        std::vector<SuperLayerConfiguration> fLayerConfiguration = {};
    };

    class CellMapManager {
    public:
        void SetOutdated() { fOutdated = true; }
        inline const std::vector<CellInformation>& Get(const CDC* cdc);

    private:
        bool fOutdated = true;
        std::vector<CellInformation> fCellMap = {};
    };

    inline void SetGeometryOutdated() const;
    std::vector<SuperLayerConfiguration> ComputeLayerConfiguration() const;
    std::vector<CellInformation> ComputeCellMap() const;

    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    ///////////////////////////////////////////////////////////
    // Geometry properties
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
    // Detection properties
    ///////////////////////////////////////////////////////////

    double fMeanDriftVelocity;
    double fTimeResolution;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/CDC.inl"
