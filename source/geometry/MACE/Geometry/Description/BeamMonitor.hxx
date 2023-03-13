#pragma once

#include "MACE/Geometry/DescriptionBase.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Geometry::Description {

class BeamMonitor final : public DescriptionSingletonBase<BeamMonitor> {
    friend Env::Memory::SingletonFactory;

private:
    BeamMonitor();
    ~BeamMonitor() = default;
    BeamMonitor(const BeamMonitor&) = delete;
    BeamMonitor& operator=(const BeamMonitor&) = delete;

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
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    bool fIsEnabled;
    double fWidth;
    double fThickness;
    double fDistanceToTargetSurface;
};

} // namespace MACE::Geometry::Description
