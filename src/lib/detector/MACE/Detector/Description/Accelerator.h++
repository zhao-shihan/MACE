#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Detector::Description {

class Accelerator final : public DescriptionSingletonBase<Accelerator> {
    friend Env::Memory::SingletonInstantiator;

private:
    Accelerator();
    ~Accelerator() = default;

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

    auto AcceleratePotential() const -> auto { return fAcceleratePotential; }

    auto AcceleratePotential(auto v) -> void { fAcceleratePotential = v, UpdateAcceleratorFieldStrength(); }

    ///////////////////////////////////////////////////////////
    // Cached value
    ///////////////////////////////////////////////////////////

    auto AcceleratorFieldStrength() const -> auto { return fAcceleratorFieldStrength; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

    auto UpdateAcceleratorFieldStrength() -> void { fAcceleratorFieldStrength = fAcceleratePotential / fAccelerateLength; }

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

    double fAcceleratePotential;

    ///////////////////////////////////////////////////////////
    // Cached value
    ///////////////////////////////////////////////////////////

    double fAcceleratorFieldStrength;
};

} // namespace MACE::Detector::Description
