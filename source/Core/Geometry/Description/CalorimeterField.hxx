#pragma once

#include "Core/Geometry/Description/TransportLine.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class CalorimeterField final : public IDescription {
public:
    static CalorimeterField& Instance() noexcept;

private:
    CalorimeterField();
    ~CalorimeterField() noexcept = default;
    CalorimeterField(const CalorimeterField&) = delete;
    CalorimeterField& operator=(const CalorimeterField&) = delete;

public:
    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D GetTransform() const;

private:
    void ReadImpl(const YAML::Node& node) override;
    void WriteImpl(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
};

} // namespace MACE::Core::Geometry::Description
