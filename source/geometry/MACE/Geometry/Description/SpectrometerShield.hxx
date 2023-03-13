#pragma once

#include "MACE/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class SpectrometerShield final : public ISingletonDescription<SpectrometerShield> {
    friend Env::Memory::SingletonFactory;

private:
    SpectrometerShield();
    ~SpectrometerShield() noexcept = default;
    SpectrometerShield(const SpectrometerShield&) = delete;
    SpectrometerShield& operator=(const SpectrometerShield&) = delete;

public:
    const auto& InnerRadius() const { return fInnerRadius; }
    const auto& InnerLength() const { return fInnerLength; }
    const auto& WindowRadius() const { return fWindowRadius; }
    const auto& Thickness() const { return fThickness; }

    void InnerRadius(double val) { fInnerRadius = val; }
    void InnerLength(double val) { fInnerLength = val; }
    void WindowRadius(double val) { fWindowRadius = val; }
    void Thickness(double val) { fThickness = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fThickness;
};

} // namespace MACE::Geometry::Description
