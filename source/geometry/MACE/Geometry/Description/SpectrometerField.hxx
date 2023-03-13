#pragma once

#include "MACE/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class SpectrometerField final : public ISingletonDescription<SpectrometerField> {
    friend Env::Memory::SingletonFactory;

private:
    SpectrometerField();
    ~SpectrometerField() noexcept = default;
    SpectrometerField(const SpectrometerField&) = delete;
    SpectrometerField& operator=(const SpectrometerField&) = delete;

public:
    const auto& Radius() const { return fRadius; }
    const auto& Length() const { return fLength; }

    void Radius(double val) { fRadius = val; }
    void Length(double val) { fLength = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
};

} // namespace MACE::Geometry::Description
