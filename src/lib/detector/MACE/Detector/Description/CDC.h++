#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Math/IntegerPower.h++"

#include "Eigen/Core"

#include "gsl/gsl"

#include <bit>
#include <cinttypes>
#include <optional>
#include <vector>

class G4Material;

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
    auto MinAdjacentSuperLayersDistance() const -> auto { return fMinAdjacentSuperLayersDistance; }
    auto MinWireAndRadialShellDistance() const -> auto { return fMinWireAndRadialShellDistance; }
    auto ShellInnerThickness() const -> auto { return fShellInnerThickness; }
    auto ShellSideThickness() const -> auto { return fShellSideThickness; }
    auto ShellOuterThickness() const -> auto { return fShellOuterThickness; }

    auto EvenSuperLayerIsAxial(bool v) -> void { fEvenSuperLayerIsAxial = v, fCache.Expire(); }
    auto NSuperLayer(int v) -> void { fNSuperLayer = v, fCache.Expire(); }
    auto NSenseLayerPerSuper(int v) -> void { fNSenseLayerPerSuper = v, fCache.Expire(); }
    auto GasInnerRadius(double v) -> void { fGasInnerRadius = v, fCache.Expire(); }
    auto GasInnerLength(double v) -> void { fGasInnerLength = v, fCache.Expire(); }
    auto EndCapSlope(double v) -> void { fEndCapSlope = v, fCache.Expire(); }
    auto MinStereoAngle(double v) -> void { fMinStereoAngle = v, fCache.Expire(); }
    auto MinCellWidth(double v) -> void { fMinCellWidth = v, fCache.Expire(); }
    auto ReferenceCellWidth(double v) -> void { fReferenceCellWidth = v, fCache.Expire(); }
    auto MaxCellWidth(double v) -> void { fMaxCellWidth = v, fCache.Expire(); }
    auto FieldWireDiameter(double v) -> void { fFieldWireDiameter = v, fCache.Expire(); }
    auto SenseWireDiameter(double v) -> void { fSenseWireDiameter = v, fCache.Expire(); }
    auto MinAdjacentSuperLayersDistance(double v) -> void { fMinAdjacentSuperLayersDistance = v, fCache.Expire(); }
    auto MinWireAndRadialShellDistance(double v) -> void { fMinWireAndRadialShellDistance = v, fCache.Expire(); }
    auto ShellInnerThickness(double v) -> void { fShellInnerThickness = v, fCache.Expire(); }
    auto ShellSideThickness(double v) -> void { fShellSideThickness = v, fCache.Expire(); }
    auto ShellOuterThickness(double v) -> void { fShellOuterThickness = v, fCache.Expire(); }

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
            auto TanStereoZenithAngle(double r) const -> auto { return r * std::tan(stereoAzimuthAngle / 2) / halfLength; }
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

    auto LayerConfiguration() const -> const auto& { return fCache.LayerConfiguration(this); }
    auto GasOuterRadius() const -> auto { return LayerConfiguration().back().outerRadius + fMinWireAndRadialShellDistance; }
    auto GasOuterLength() const -> auto { return fGasInnerLength + 2 * fEndCapSlope * (GasOuterRadius() - fGasInnerRadius); }

    struct CellInformation {
        int cellID;
        int cellLocalID;
        int senseLayerID;
        int senseLayerLocalID;
        int superLayerID;
        Eigen::Vector2d position;
        Eigen::Vector3d direction;
    };

    auto CellMap() const -> const auto& { return fCache.CellMap(this); }
    auto CellMapFromSenseLayerIDAndLocalCellID() const -> const auto& { return fCache.CellMapFromSenseLayerIDAndLocalCellID(this); }

    ///////////////////////////////////////////////////////////
    // Material
    ///////////////////////////////////////////////////////////

    auto ButaneFraction() const -> auto { return fButaneFraction; }

    auto ButaneFraction(double v) -> void { fButaneFraction = v; }

    auto GasMaterial() const -> G4Material*;

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

    struct HashArray2i32 {
        constexpr auto operator()(stdx::array2i32 i) const -> std::size_t {
            return std::bit_cast<std::uint64_t>(i);
        }
    };

public:
    using CellMapFromSenseLayerIDAndLocalCellIDType = std::unordered_map<stdx::array2i32, CellInformation, HashArray2i32>;

private:
    class Cache {
    public:
        inline auto Expire() -> void;

        inline auto LayerConfiguration(const CDC* cdc) -> const std::vector<SuperLayerConfiguration>&;
        inline auto CellMap(const CDC* cdc) -> const std::vector<CellInformation>&;
        inline auto CellMapFromSenseLayerIDAndLocalCellID(const CDC* cdc) -> const CellMapFromSenseLayerIDAndLocalCellIDType&;

    private:
        std::optional<std::vector<SuperLayerConfiguration>> fLayerConfiguration{};
        std::optional<std::vector<CellInformation>> fCellMap{};
        std::optional<CellMapFromSenseLayerIDAndLocalCellIDType> fCellMapFromSenseLayerIDAndLocalCellID{};
    };

    auto ComputeLayerConfiguration() const -> std::vector<SuperLayerConfiguration>;
    auto ComputeCellMap() const -> std::vector<CellInformation>;
    auto ComputeCellMapFromSenseLayerIDAndLocalCellID() const -> CellMapFromSenseLayerIDAndLocalCellIDType;

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
    double fMinAdjacentSuperLayersDistance;
    double fMinWireAndRadialShellDistance;
    double fShellInnerThickness;
    double fShellSideThickness;
    double fShellOuterThickness;

    mutable Cache fCache;

    ///////////////////////////////////////////////////////////
    // Material
    ///////////////////////////////////////////////////////////

    double fButaneFraction;

    ///////////////////////////////////////////////////////////
    // Detection
    ///////////////////////////////////////////////////////////

    double fMeanDriftVelocity;
    double fTimeResolutionFWHM;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/CDC.inl"
