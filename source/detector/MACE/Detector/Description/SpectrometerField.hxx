#pragma once

#include "MACE/Detector/DescriptionBase.hxx"

namespace MACE::Detector::Description {

class SpectrometerField final : public DescriptionSingletonBase<SpectrometerField> {
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

} // namespace MACE::Detector::Description
