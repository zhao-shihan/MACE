#pragma once

#include "MACE/Detector/DescriptionBase.hxx"

namespace MACE::Detector::Description {

class SpectrometerMagnet final : public DescriptionSingletonBase<SpectrometerMagnet> {
    friend Env::Memory::SingletonFactory;

private:
    SpectrometerMagnet();
    ~SpectrometerMagnet() noexcept = default;
    SpectrometerMagnet(const SpectrometerMagnet&) = delete;
    SpectrometerMagnet& operator=(const SpectrometerMagnet&) = delete;

public:
    const auto& InnerRadius() const { return fInnerRadius; }
    const auto& OuterRadius() const { return fOuterRadius; }
    const auto& Length() const { return fLength; }

    void InnerRadius(double val) { fInnerRadius = val; }
    void OuterRadius(double val) { fOuterRadius = val; }
    void Length(double val) { fLength = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fOuterRadius;
    double fLength;
};

} // namespace MACE::Detector::Description
