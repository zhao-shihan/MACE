#pragma once

#include "MACE/Geometry/DescriptionBase.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Geometry::Description {

class EMCalField final : public DescriptionSingletonBase<EMCalField> {
    friend Env::Memory::SingletonFactory;

private:
    EMCalField();
    ~EMCalField() noexcept = default;
    EMCalField(const EMCalField&) = delete;
    EMCalField& operator=(const EMCalField&) = delete;

public:
    const auto& Radius() const { return fRadius; }
    const auto& Length() const { return fLength; }

    void Radius(double val) { fRadius = val; }
    void Length(double val) { fLength = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
};

} // namespace MACE::Geometry::Description
