#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class SpectrometerMagnet final : public DescriptionSingletonBase<SpectrometerMagnet> {
    friend Env::Memory::SingletonFactory;

private:
    SpectrometerMagnet();
    ~SpectrometerMagnet() noexcept = default;

public:
    const auto& InnerRadius() const { return fInnerRadius; }
    const auto& OuterRadius() const { return fOuterRadius; }
    const auto& Length() const { return fLength; }

    void InnerRadius(double val) { fInnerRadius = val; }
    void OuterRadius(double val) { fOuterRadius = val; }
    void Length(double val) { fLength = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fOuterRadius;
    double fLength;
};

} // namespace MACE::Detector::Description
