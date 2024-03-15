#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class SpectrometerShield final : public DescriptionSingletonBase<SpectrometerShield> {
    friend Env::Memory::SingletonInstantiator;

private:
    SpectrometerShield();
    ~SpectrometerShield() = default;

public:
    // Geometry

    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto InnerLength() const -> auto { return fInnerLength; }
    auto Thickness() const -> auto { return fThickness; }
    auto WindowRadius() const -> auto { return fWindowRadius; }
    auto BeamSlantAngle() const -> auto { return fBeamSlantAngle; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto InnerLength(double val) -> void { fInnerLength = val; }
    auto Thickness(double val) -> void { fThickness = val; }
    auto WindowRadius(double val) -> void { fWindowRadius = val; }
    auto BeamSlantAngle(double val) -> void { fBeamSlantAngle = val; }

    // Material

    auto MaterialName() const -> const auto& { return fMaterialName; }

    auto MaterialName(std::string val) -> void { fMaterialName = std::move(val); }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    // Geometry

    double fInnerRadius;
    double fInnerLength;
    double fThickness;
    double fWindowRadius;
    double fBeamSlantAngle;

    // Material

    std::string fMaterialName;
};

} // namespace MACE::Detector::Description
