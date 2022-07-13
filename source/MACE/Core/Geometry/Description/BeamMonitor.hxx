#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class BeamMonitor final : public IDescriptionSingleton<BeamMonitor> {
    friend Singleton<BeamMonitor>;

private:
    BeamMonitor();
    ~BeamMonitor() noexcept = default;
    BeamMonitor(const BeamMonitor&) = delete;
    BeamMonitor& operator=(const BeamMonitor&) = delete;

public:
    const auto& IsEnabled() const { return fIsEnabled; }
    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }
    const auto& GetDistanceToTargetSurface() const { return fDistanceToTargetSurface; }

    void SetEnable(bool val) { fIsEnabled = val; }
    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetDistanceToTargetSurface(double val) { fDistanceToTargetSurface = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    bool fIsEnabled;
    double fWidth;
    double fThickness;
    double fDistanceToTargetSurface;
};

} // namespace MACE::Core::Geometry::Description
