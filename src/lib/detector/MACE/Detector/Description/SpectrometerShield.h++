#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class SpectrometerShield final : public DescriptionSingletonBase<SpectrometerShield> {
    friend Env::Memory::SingletonFactory;

private:
    SpectrometerShield();
    ~SpectrometerShield() noexcept = default;

public:
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto InnerLength() const -> const auto& { return fInnerLength; }
    auto WindowRadius() const -> const auto& { return fWindowRadius; }
    auto Thickness() const -> const auto& { return fThickness; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto InnerLength(double val) -> void { fInnerLength = val; }
    auto WindowRadius(double val) -> void { fWindowRadius = val; }
    auto Thickness(double val) -> void { fThickness = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fThickness;
};

} // namespace MACE::Detector::Description
