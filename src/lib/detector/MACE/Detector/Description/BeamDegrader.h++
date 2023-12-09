#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Detector::Description {

class BeamDegrader final : public DescriptionSingletonBase<BeamDegrader> {
    friend Env::Memory::SingletonFactory;

private:
    BeamDegrader();
    ~BeamDegrader() = default;

public:
    const auto& Enabled() const { return fIsEnabled; }
    const auto& Width() const { return fWidth; }
    const auto& Thickness() const { return fThickness; }
    const auto& DistanceToTargetSurface() const { return fDistanceToTargetSurface; }

    void Enabled(bool val) { fIsEnabled = val; }
    void Width(double val) { fWidth = val; }
    void Thickness(double val) { fThickness = val; }
    void DistanceToTargetSurface(double val) { fDistanceToTargetSurface = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    bool fIsEnabled;
    double fWidth;
    double fThickness;
    double fDistanceToTargetSurface;
};

} // namespace MACE::Detector::Description
