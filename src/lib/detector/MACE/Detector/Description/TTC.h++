#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class TTC final : public DescriptionSingletonBase<TTC> {
    friend Env::Memory::SingletonInstantiator;

private:
    TTC();
    ~TTC() = default;

public:
    // Geometry

    auto Length() const -> auto { return fLength; }
    auto Width() const -> auto { return fWidth; }
    auto Thickness() const -> auto { return fThickness; }
    auto Radius() const -> auto { return fRadius; }
    auto SlantAngle() const -> auto { return fSlantAngle; }
    auto NAlongPhi() const -> auto { return fNAlongPhi; }
    auto NAlongZ() const -> auto { return fNAlongZ; }

    auto Length(double val) -> void { fLength = val; }
    auto Width(double val) -> void { fWidth = val; }
    auto Thickness(double val) -> void { fThickness = val; }
    auto Radius(double val) -> void { fRadius = val; }
    auto SlantAngle(double val) -> void { fSlantAngle = val; }
    auto NAlongPhi(int val) -> void { fNAlongPhi = val; }
    auto NAlongZ(int val) -> void { fNAlongZ = val; }

    // Material

    auto Density() const -> auto { return fDensity; }
    auto RIndexEnergyBin() const -> const auto& { return fRIndexEnergyBin; }
    auto RIndex() const -> const auto& { return fRIndex; }
    auto AbsLengthEnergyBin() const -> const auto& { return fAbsLengthEnergyBin; }
    auto AbsLength() const -> const auto& { return fAbsLength; }
    auto ScintillationComponent1EnergyBin() const -> const auto& { return fScintillationComponent1EnergyBin; }
    auto ScintillationComponent1() const -> const auto& { return fScintillationComponent1; }
    auto ScintillationYield() const -> auto { return fScintillationYield; }
    auto ScintillationTimeConstant1() const -> auto { return fScintillationTimeConstant1; }
    auto ResolutionScale() const -> auto { return fResolutionScale; }

    auto Density(double val) -> void { fDensity = val; }
    auto RIndexEnergyBin(std::vector<double> val) -> void { fRIndexEnergyBin = std::move(val); }
    auto RIndex(std::vector<double> val) -> void { fRIndex = std::move(val); }
    auto AbsLengthEnergyBin(std::vector<double> val) -> void { fAbsLengthEnergyBin = std::move(val); }
    auto AbsLength(std::vector<double> val) -> void { fAbsLength = std::move(val); }
    auto ScintillationComponent1EnergyBin(std::vector<double> val) -> void { fScintillationComponent1EnergyBin = std::move(val); }
    auto ScintillationComponent1(std::vector<double> val) -> void { fScintillationComponent1 = std::move(val); }
    auto ScintillationYield(double val) -> void { fScintillationYield = val; }
    auto ScintillationTimeConstant1(double val) -> void { fScintillationTimeConstant1 = val; }
    auto ResolutionScale(double val) -> void { fResolutionScale = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    // Geometry

    double fLength;
    double fWidth;
    double fThickness;
    double fRadius;
    double fSlantAngle;
    int fNAlongPhi;
    int fNAlongZ;

    // Material

    double fDensity;
    std::vector<double> fRIndexEnergyBin;
    std::vector<double> fRIndex;
    std::vector<double> fAbsLengthEnergyBin;
    std::vector<double> fAbsLength;
    std::vector<double> fScintillationComponent1EnergyBin;
    std::vector<double> fScintillationComponent1;
    double fScintillationYield;
    double fScintillationTimeConstant1;
    double fResolutionScale;
};

} // namespace MACE::Detector::Description
