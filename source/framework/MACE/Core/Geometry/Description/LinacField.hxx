#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class LinacField final : public ISingletonDescription<LinacField> {
    friend Environment::Memory::SingletonFactory;

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

} // namespace MACE::Core::Geometry::Description
