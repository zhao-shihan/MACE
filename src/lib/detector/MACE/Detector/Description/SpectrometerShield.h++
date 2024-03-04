#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class SpectrometerShield final : public DescriptionSingletonBase<SpectrometerShield> {
    friend Env::Memory::SingletonInstantiator;

private:
    SpectrometerShield();
    ~SpectrometerShield() noexcept = default;

public:
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

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fThickness;
    double fWindowRadius;
    double fBeamSlantAngle;
};

} // namespace MACE::Detector::Description
