#pragma once

#include "Mustard/Detector/Description/DescriptionWithCacheBase.h++"

#include "muc/array"

#include <string>
#include <utility>

namespace MACE::PhaseI::Detector::Description {

class SciFiTracker final : public Mustard::Detector::Description::DescriptionWithCacheBase<SciFiTracker> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    SciFiTracker();
    ~SciFiTracker() = default;

public:
    // Geometry
    auto EpoxyThickness() const -> auto { return fEpoxyThickness; }
    auto SiliconeOilThickness() const -> auto { return fSiliconeOilThickness; }
    auto SiPMLength() const -> auto { return fSiPMLength; }
    auto SiPMWidth() const -> auto { return fSiPMWidth; }
    auto SiPMThickness() const -> auto { return fSiPMThickness; }
    auto FiberCoreWidth() const -> auto { return fFiberCoreWidth; }
    auto FiberCladdingWidth() const -> auto { return fFiberCladdingWidth; }
    auto LightGuideCurvature() const -> auto { return fLightGuideCurvature; }
    auto FiberLength() const -> auto { return fFiberLength; }
    auto TLightGuideLength() const -> auto { return fTLightGuideLength; }
    auto DetectorLayerConfiguration() const -> const auto& { return *fLayerConfiguration; }
    auto NLayer() const -> auto { return *fNLayer; }
    auto TypeOfLayer() const -> auto& { return fTypeOfLayer; }
    auto RLayer() const -> const auto& { return fRLayer; }
    auto IsSecond() const -> const auto& { return fIsSecond; }
    auto BeginIDOfLayer() const -> const auto& { return fBeginIDOfLayer; }
    auto EndIDOfLayer() const -> const auto& { return fEndIDOfLayer; }
    auto NameOfLayer() const -> auto& { return fNameOfLayer; }
    auto CombinationOfLayer() const -> auto& { return fCombinationOfLayer; }
    // Optical properties
    auto ScintillationTimeConstant1() const -> auto { return fScintillationTimeConstant1; }
    auto ScintillationWaveLengthBin() const -> const auto& { return fScintillationWavelengthBin; }
    auto ScintillationComponent1() const -> const auto& { return fScintillationComponent1; }
    auto SiPMEnergyBin() const -> const auto& { return fSiPMEnergyBin; }
    auto SiPMQuantumEfficiency() const -> const auto& { return fSiPMQuantumEfficiency; }
    //// reconstruction////
    auto Threshold() const -> const auto { return fThreshold; }
    auto ClusterLength() const -> const auto { return fClusterLength; }
    auto ThresholdTime() const -> const auto { return fThresholdTime; }
    auto TimeWindow() const -> const auto { return fTimeWindow; }
    auto DeadTime() const -> const auto { return fDeadtime; }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    auto EpoxyThickness(double val) -> void { fEpoxyThickness = val; }
    auto SiliconeOilThickness(double val) -> void { fSiliconeOilThickness = val; }
    auto SiPMLength(double val) -> void { fSiPMLength = val; }
    auto SiPMWidth(double val) -> void { fSiPMWidth = val; }
    auto SiPMThickness(double val) -> void { fSiPMThickness = val; }
    auto FiberCoreRadius(double val) -> void { fFiberCoreWidth = val; }
    auto FiberCladdingRadius(double val) -> void { fFiberCladdingWidth = val; }
    auto LightGuideCurvature(double val) -> void { fLightGuideCurvature = val; }
    auto FiberLength(double val) -> void { fFiberLength = val; }
    auto TLightGuideLength(double val) -> void { fTLightGuideLength = val; }
    auto ScintillationTimeConstant1(double val) -> void { fScintillationTimeConstant1 = val; }
    auto NLayer(int val) -> void { fNLayer = val; }
    auto TypeOfLayer(std::vector<char> val) -> void { fTypeOfLayer = std::move(val); }
    auto RLayer(std::vector<double> val) -> void { fRLayer = std::move(val); }
    auto IsSecond(std::vector<bool> val) -> void { fIsSecond = std::move(val); }
    auto BeginIDOfLayer(std::vector<int> val) -> void { fBeginIDOfLayer = std::move(val); }
    auto EndIDOfLayer(std::vector<int> val) -> void { fEndIDOfLayer = std::move(val); }
    auto NameOfLayer(std::vector<std::string> val) -> void { fNameOfLayer = std::move(val); }
    auto CombinationOfLayer(std::vector<std::vector<int>> val) -> void { fCombinationOfLayer = std::move(val); }

    auto ScintillationWaveLengthBin(std::vector<double> val) -> void { fScintillationWavelengthBin = std::move(val); }
    auto ScintillationComponent1(std::vector<double> val) -> void { fScintillationComponent1 = std::move(val); }
    auto SiPMEnergyBin(std::vector<double> val) -> void { fSiPMEnergyBin = std::move(val); }
    auto SiPMQuantumEfficiency(std::vector<double> val) -> void { fSiPMQuantumEfficiency = std::move(val); }

    auto Threshold(int val) -> void { fThreshold = val; }
    auto ClusterLength(int val) -> void { fClusterLength = val; }
    auto ThresholdTime(double val) -> void { fThresholdTime = val; }
    auto TimeWindow(double val) -> void { fTimeWindow = val; }
    auto DeadTime(double val) -> void { fDeadtime = val; }

public:
    struct LayerConfiguration {
        struct FiberConfiguration {
            char layerType;
            double radius;
            double pitch;
        };
        int beginID;
        int endID;
        bool isSecond;
        std::string name;
        FiberConfiguration fiber;
    };

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    double fSiliconeOilThickness;
    double fFiberCoreWidth;
    double fFiberCladdingWidth;
    double fFiberLength;
    double fLightGuideCurvature;
    double fSiPMLength;
    double fTLightGuideLength;
    double fSiPMWidth;
    double fSiPMThickness;
    double fEpoxyThickness;

    double fScintillationYield;
    double fScintillationTimeConstant1;
    double fResolutionScale;

    int fThreshold;
    int fClusterLength;
    double fThresholdTime;
    double fTimeWindow;
    double fDeadtime;
    std::vector<double> fScintillationWavelengthBin;
    std::vector<double> fScintillationComponent1;
    std::vector<double> fSiPMEnergyBin;
    std::vector<double> fSiPMQuantumEfficiency;

    auto CalculateLayerConfiguration() const -> std::vector<LayerConfiguration>;
    auto CalculateLayerPitch() const -> std::vector<double>;
    Simple<int> fNLayer;
    Simple<std::vector<char>> fTypeOfLayer;
    Simple<std::vector<double>> fRLayer;
    Simple<std::vector<bool>> fIsSecond;
    Simple<std::vector<int>> fBeginIDOfLayer;
    Simple<std::vector<int>> fEndIDOfLayer;
    Simple<std::vector<std::string>> fNameOfLayer;
    Simple<std::vector<std::vector<int>>> fCombinationOfLayer;
    Cached<std::vector<double>> fPitchOfLayer;
    Cached<std::vector<LayerConfiguration>> fLayerConfiguration;
};

} // namespace MACE::PhaseI::Detector::Description
