#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class EMCalField final : public ISingletonDescription<EMCalField> {
    friend Environment::Memory::SingletonFactory;

private:
    EMCalField();
    ~EMCalField() noexcept = default;
    EMCalField(const EMCalField&) = delete;
    EMCalField& operator=(const EMCalField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
