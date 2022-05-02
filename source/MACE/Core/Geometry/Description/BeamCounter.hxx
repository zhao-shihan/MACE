#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class BeamCounter final : public IDescription {
public:
    static BeamCounter& Instance() noexcept;

private:
    BeamCounter();
    ~BeamCounter() noexcept = default;
    BeamCounter(const BeamCounter&) = delete;
    BeamCounter& operator=(const BeamCounter&) = delete;

public:
    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }
    const auto& GetDistanceToTargetSurface() const { return fDistanceToTargetSurface; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetDistanceToTargetSurface(double val) { fDistanceToTargetSurface = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    void ReadImpl(const YAML::Node& node) override;
    void WriteImpl(YAML::Node& node) const override;

private:
    double fWidth;
    double fThickness;
    double fDistanceToTargetSurface;
};

} // namespace MACE::Core::Geometry::Description
