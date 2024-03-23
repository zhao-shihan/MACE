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

    auto MaterialName() const -> const auto& { return fMaterialName; }

    auto MaterialName(std::string val) -> void { fMaterialName = std::move(val); }

    // Detection

    auto TimeResolutionFWHM() const -> auto { return fTimeResolutionFWHM; }

    auto TimeResolutionFWHM(double val) -> void { fTimeResolutionFWHM = val; }

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

    std::string fMaterialName;

    // Detection

    double fTimeResolutionFWHM;
};

} // namespace MACE::Detector::Description
