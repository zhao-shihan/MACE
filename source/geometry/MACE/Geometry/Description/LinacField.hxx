#pragma once

#include "MACE/Geometry/DescriptionBase.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Geometry::Description {

class LinacField final : public DescriptionSingletonBase<LinacField> {
    friend Env::Memory::SingletonFactory;

private:
    LinacField();
    ~LinacField() noexcept = default;
    LinacField(const LinacField&) = delete;
    LinacField& operator=(const LinacField&) = delete;

public:
    const auto& Radius() const { return fRadius; }
    const auto& Length() const { return fLength; }
    const auto& DownStreamLength() const { return fDownStreamLength; }

    void Radius(double val) { fRadius = val; }
    void Length(double val) { fLength = val; }
    void DownStreamLength(double val) { fDownStreamLength = val; }

    HepGeom::Transform3D CalcTransform() const;

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fRadius;
    double fLength;
    double fDownStreamLength;
};

} // namespace MACE::Geometry::Description
