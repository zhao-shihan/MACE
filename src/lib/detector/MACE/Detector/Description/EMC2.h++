#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "Eigen/Core"

namespace MACE::Detector::Description {

class EMC final : public DescriptionSingletonBase<EMC> {
    friend Env::Memory::SingletonFactory;

private:
    EMC();

public:
    auto NSubdivision() const -> const auto& { return fNSubdivision; }
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto CrystalLength() const -> const auto& { return fCrystalLength; }
    auto PMTRadius() const -> const auto& { return fPMTRadius; }
    auto PMTCouplerThickness() const -> const auto& { return fPMTCouplerThickness; }
    auto PMTWindowThickness() const -> auto& { return fPMTWindowThickness; }
    auto PMTCathodeThickness() const -> auto& { return fPMTCathodeThickness; }

    auto CouplerEnergyBin() const -> auto& { return fCouplerEnergyBin; }
    auto CouplerRefractiveIndex() const -> auto& { return fCouplerRefractiveIndex; }
    auto PMTWaveLengthBin() const -> auto& { return fPMTWaveLengthBin; }
    auto PMTQuantumEfficiency() const -> auto& { return fPMTQuantumEfficiency; }
    auto CsIEnergyBin() const -> auto& { return fCsIEnergyBin; }
    auto CsIScintillationComponent1() const -> auto& { return fCsIScintillationComponent1; }

    auto ScintillationYield() const -> auto& { return fScintillationYield; }
    auto ScintillationTimeConstant1() const -> auto& { return fScintillationTimeConstant1; }
    auto ResolutionScale() const -> auto& { return fResolutionScale; }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    auto NSubdivision(const auto& val) -> void { fNSubdivision = val; }
    auto InnerRadius(const auto& val) -> void { fInnerRadius = val; }
    auto CrystalLength(const auto& val) -> void { fCrystalLength = val; }
    auto PMTRadius(const auto& val) -> void { fPMTRadius = val; }
    auto PMTCouplerThickness(const auto& val) -> void { fPMTCouplerThickness = val; }
    auto PMTWindowThickness(const auto& val) -> void { fPMTWindowThickness = val; }
    auto PMTCathodeThickness(const auto& val) -> void { fPMTCathodeThickness = val; }

    auto CoupleEnergyBin(const auto& val) -> void { fCouplerEnergyBin = val; }
    auto CouplerRefractiveIndex(const auto& val) -> void { fCouplerRefractiveIndex = val; }
    auto PMTWaveLengthBin(const auto& val) -> void { fPMTWaveLengthBin = val; }
    auto PMTQuantumEfficiency(const auto& val) -> void { fPMTQuantumEfficiency = val; }
    auto CsIEnergyBin(const auto& val) -> void { fCsIEnergyBin = val; }
    auto CsIScintillationComponent1(const auto& val) -> void { fCsIScintillationComponent1 = val; }

    auto ScintillationYield(const auto& val) -> void { fScintillationYield = val; }
    auto ScintillationTimeConstant1(const auto& val) -> void { fScintillationTimeConstant1 = val; }
    auto ResolutionScale(const auto& val) -> void { fResolutionScale = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    int fNSubdivision;
    double fInnerRadius;
    double fCrystalLength;
    double fPMTRadius;
    double fPMTCouplerThickness;
    double fPMTWindowThickness;
    double fPMTCathodeThickness;

    std::vector<double> fCouplerEnergyBin;
    std::vector<double> fCouplerRefractiveIndex;
    std::vector<double> fPMTWaveLengthBin;
    std::vector<double> fPMTQuantumEfficiency;
    std::vector<double> fCsIEnergyBin;
    std::vector<double> fCsIScintillationComponent1;

    double fScintillationYield;
    double fScintillationTimeConstant1;
    double fResolutionScale;
};

} // namespace MACE::Detector::Description
