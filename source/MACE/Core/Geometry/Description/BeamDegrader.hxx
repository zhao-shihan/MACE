#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class BeamDegrader final : public IDescription {
public:
    static BeamDegrader& Instance() noexcept;

private:
    BeamDegrader();
    ~BeamDegrader() noexcept = default;
    BeamDegrader(const BeamDegrader&) = delete;
    BeamDegrader& operator=(const BeamDegrader&) = delete;

public:
    const auto& IsEnabled() const { return fIsEnabled; }
    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }
    const auto& GetDistanceToTargetSurface() const { return fDistanceToTargetSurface; }

    void SetEnabled(bool val) { fIsEnabled = val; }
    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetDistanceToTargetSurface(double val) { fDistanceToTargetSurface = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    void ReadImpl(const YAML::Node& node) override;
    void WriteImpl(YAML::Node& node) const override;

private:
    bool fIsEnabled;
    double fWidth;
    double fThickness;
    double fDistanceToTargetSurface;
};

} // namespace MACE::Core::Geometry::Description
