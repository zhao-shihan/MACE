#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Detector::Description {

class BeamDegrader final : public DescriptionSingletonBase<BeamDegrader> {
    friend Env::Memory::SingletonInstantiator;

private:
    BeamDegrader();
    ~BeamDegrader() = default;

public:
    auto Enabled() const -> auto { return fEnabled; }
    auto Width() const -> auto { return fWidth; }
    auto Thickness() const -> auto { return fThickness; }
    auto DistanceToTargetSurface() const -> auto { return fDistanceToTargetSurface; }

    auto Enabled(bool val) -> void { fEnabled = val; }
    auto Width(double val) -> void { fWidth = val; }
    auto Thickness(double val) -> void { fThickness = val; }
    auto DistanceToTargetSurface(double val) -> void { fDistanceToTargetSurface = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    bool fEnabled;
    double fWidth;
    double fThickness;
    double fDistanceToTargetSurface;
};

} // namespace MACE::Detector::Description
