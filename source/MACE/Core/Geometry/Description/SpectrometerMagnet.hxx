#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SpectrometerMagnet final : public IDescriptionSingleton<SpectrometerMagnet> {
    friend Singleton<SpectrometerMagnet>::Signature;

private:
    SpectrometerMagnet();
    ~SpectrometerMagnet() noexcept = default;
    SpectrometerMagnet(const SpectrometerMagnet&) = delete;
    SpectrometerMagnet& operator=(const SpectrometerMagnet&) = delete;

public:
    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetOuterRadius() const { return fOuterRadius; }
    const auto& GetLength() const { return fLength; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fOuterRadius;
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
