#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "Eigen/Core"

#include "muc/array"
#include "muc/math"

#include "gsl/gsl"

#include <bit>
#include <cinttypes>
#include <optional>
#include <vector>

class G4Material;

namespace MACE::Detector::Description {

class CDC final : public DescriptionBase<CDC> {
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
    auto CellWidthLowerBound() const -> auto { return fCellWidthLowerBound; }
    auto ReferenceCellWidth() const -> auto { return fReferenceCellWidth; }
    auto CellWidthUpperBound() const -> auto { return fCellWidthUpperBound; }
    auto FieldWireDiameter() const -> auto { return fFieldWireDiameter; }
    auto SenseWireDiameter() const -> auto { return fSenseWireDiameter; }
    auto MinAdjacentSuperLayersDistance() const -> auto { return fMinAdjacentSuperLayersDistance; }
    auto MinWireAndRadialShellDistance() const -> auto { return fMinWireAndRadialShellDistance; }
    auto EndCapThickness() const -> auto { return fEndCapThickness; }
    auto InnerShellAlThickness() const -> auto { return fInnerShellAlThickness; }
    auto InnerShellMylarThickness() const -> auto { return fInnerShellMylarThickness; }
    auto OuterShellThickness() const -> auto { return fOuterShellThickness; }

    auto EvenSuperLayerIsAxial(bool val) -> void { fEvenSuperLayerIsAxial = val, fCache.Expire(); }
    auto NSuperLayer(int val) -> void { fNSuperLayer = val, fCache.Expire(); }
    auto NSenseLayerPerSuper(int val) -> void { fNSenseLayerPerSuper = val, fCache.Expire(); }
    auto GasInnerRadius(double val) -> void { fGasInnerRadius = val, fCache.Expire(); }
    auto GasInnerLength(double val) -> void { fGasInnerLength = val, fCache.Expire(); }
    auto EndCapSlope(double val) -> void { fEndCapSlope = val, fCache.Expire(); }
    auto MinStereoAngle(double val) -> void { fMinStereoAngle = val, fCache.Expire(); }
    auto CellWidthLowerBound(double val) -> void { fCellWidthLowerBound = val, fCache.Expire(); }
    auto ReferenceCellWidth(double val) -> void { fReferenceCellWidth = val, fCache.Expire(); }
    auto CellWidthUpperBound(double val) -> void { fCellWidthUpperBound = val, fCache.Expire(); }
    auto FieldWireDiameter(double val) -> void { fFieldWireDiameter = val, fCache.Expire(); }
    auto SenseWireDiameter(double val) -> void { fSenseWireDiameter = val, fCache.Expire(); }
    auto MinAdjacentSuperLayersDistance(double val) -> void { fMinAdjacentSuperLayersDistance = val, fCache.Expire(); }
    auto MinWireAndRadialShellDistance(double val) -> void { fMinWireAndRadialShellDistance = val, fCache.Expire(); }
    auto EndCapThickness(double val) -> void { fEndCapThickness = val, fCache.Expire(); }
    auto InnerShellAlThickness(double val) -> void { fInnerShellAlThickness = val, fCache.Expire(); }
    auto InnerShellMylarThickness(double val) -> void { fInnerShellMylarThickness = val, fCache.Expire(); }
    auto OuterShellThickness(double val) -> void { fOuterShellThickness = val, fCache.Expire(); }

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
            auto SecStereoZenithAngle(double r) const -> auto { return std::sqrt(1 + muc::pow<2>(TanStereoZenithAngle(r))); }
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

    auto GasButaneFraction() const -> auto { return fGasButaneFraction; }
    auto EndCapMaterialName() const -> const auto& { return fEndCapMaterialName; }
    auto OuterShellCFRPDensity() const -> auto { return fOuterShellCFRPDensity; }

    auto GasButaneFraction(double val) -> void { fGasButaneFraction = val; }
    auto EndCapMaterialName(std::string val) -> void { fEndCapMaterialName = std::move(val); }
    auto OuterShellCFRPDensity(double val) -> void { fOuterShellCFRPDensity = val; }

    auto GasMaterial() const -> G4Material*;

    ///////////////////////////////////////////////////////////
    // Detection
    ///////////////////////////////////////////////////////////

    auto MeanDriftVelocity() const -> auto { return fMeanDriftVelocity; }
    auto TimeResolutionFWHM() const -> auto { return fTimeResolutionFWHM; }

    auto MeanDriftVelocity(double val) -> void { fMeanDriftVelocity = val; }
    auto TimeResolutionFWHM(double val) -> void { fTimeResolutionFWHM = val; }

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    struct HashArray2i32 {
        constexpr auto operator()(muc::array2i32 i) const -> std::size_t {
            return std::bit_cast<std::uint64_t>(i);
        }
    };

public:
    using CellMapFromSenseLayerIDAndLocalCellIDType = std::unordered_map<muc::array2i32, CellInformation, HashArray2i32>;

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

    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

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
    double fCellWidthLowerBound;
    double fReferenceCellWidth;
    double fCellWidthUpperBound;
    double fFieldWireDiameter;
    double fSenseWireDiameter;
    double fMinAdjacentSuperLayersDistance;
    double fMinWireAndRadialShellDistance;
    double fEndCapThickness;
    double fInnerShellAlThickness;
    double fInnerShellMylarThickness;
    double fOuterShellThickness;

    mutable Cache fCache;

    ///////////////////////////////////////////////////////////
    // Material
    ///////////////////////////////////////////////////////////

    double fGasButaneFraction;
    std::string fEndCapMaterialName;
    double fOuterShellCFRPDensity;

    ///////////////////////////////////////////////////////////
    // Detection
    ///////////////////////////////////////////////////////////

    double fMeanDriftVelocity;
    double fTimeResolutionFWHM;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/CDC.inl"
