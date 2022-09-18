#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SpectrometerMagnet final : public ISingletonDescription<SpectrometerMagnet> {
    friend Environment::Memory::SingletonFactory;

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

} // namespace MACE::Core::Geometry::Description
