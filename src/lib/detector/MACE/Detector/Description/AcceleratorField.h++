#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Detector::Description {

class AcceleratorField final : public DescriptionSingletonBase<AcceleratorField> {
    friend Env::Memory::SingletonInstantiator;

private:
    AcceleratorField();
    ~AcceleratorField() = default;

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    auto Radius() const -> auto { return fRadius; }
    auto UpstreamLength() const -> auto { return fUpstreamLength; }
    auto AccelerateLength() const -> auto { return fAccelerateLength; }

    auto Radius(double v) -> void { fRadius = v; }
    auto UpstreamLength(double v) -> void { fUpstreamLength = v; }
    auto AccelerateLength(double v) -> void { fAccelerateLength = v, UpdateAcceleratorFieldStrength(); }

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    auto AcceleratorPotential() const -> auto { return fAcceleratorPotential; }

    auto AcceleratorPotential(auto v) -> void { fAcceleratorPotential = v, UpdateAcceleratorFieldStrength(); }

    ///////////////////////////////////////////////////////////
    // Cached value
    ///////////////////////////////////////////////////////////

    auto AcceleratorFieldStrength() const -> auto { return fAcceleratorFieldStrength; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

    auto UpdateAcceleratorFieldStrength() -> void { fAcceleratorFieldStrength = fAcceleratorPotential / fAccelerateLength; }

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    double fRadius;
    double fUpstreamLength;
    double fAccelerateLength;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    double fAcceleratorPotential;

    ///////////////////////////////////////////////////////////
    // Cached value
    ///////////////////////////////////////////////////////////

    double fAcceleratorFieldStrength;
};

} // namespace MACE::Detector::Description
