#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class AcceleratorField final : public IDescription {
public:
    static AcceleratorField& Instance() noexcept;

private:
    AcceleratorField();
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    const auto& GetDownStreamLength() const { return fDownStreamLength; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetDownStreamLength(double val) { fDownStreamLength = val; }

    HepGeom::Transform3D CalcTransform() const;

private:
    void ReadImpl(const YAML::Node& node) override;
    void WriteImpl(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
    double fDownStreamLength;
};

} // namespace MACE::Core::Geometry::Description
