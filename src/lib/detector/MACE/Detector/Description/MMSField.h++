#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class MMSField final : public DescriptionBase<MMSField> {
    friend Env::Memory::SingletonInstantiator;

private:
    MMSField();
    ~MMSField() = default;

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
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

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
