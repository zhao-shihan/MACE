#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class SpectrometerField final : public DescriptionSingletonBase<SpectrometerField> {
    friend Env::Memory::SingletonFactory;

private:
    SpectrometerField();
    ~SpectrometerField() = default;

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    const auto& Radius() const { return fRadius; }
    const auto& Length() const { return fLength; }

    void Radius(auto val) { fRadius = val; }
    void Length(auto val) { fLength = val; }

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    const auto& MagneticFluxDensity() const { return fMagneticFluxDensity; }

    void MagneticFluxDensity(auto v) { fMagneticFluxDensity = v; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    double fRadius;
    double fLength;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    double fMagneticFluxDensity;
};

} // namespace MACE::Detector::Description
