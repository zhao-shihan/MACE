#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Detector::Description {

class Solenoid final : public DescriptionSingletonBase<Solenoid> {
    friend Env::Memory::SingletonFactory;

private:
    Solenoid();

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    const auto& S1Length() const { return fS1Length; }
    const auto& B1Radius() const { return fB1Radius; }
    const auto& S2Length() const { return fS2Length; }
    const auto& B2Radius() const { return fB2Radius; }
    const auto& S3Length() const { return fS3Length; }
    const auto& InnerRadius() const { return fInnerRadius; }
    const auto& OuterRadius() const { return fOuterRadius; }
    const auto& FieldRadius() const { return fFieldRadius; }

    void S1Length(auto v) { fS1Length = v; }
    void B1Radius(auto v) { fB1Radius = v; }
    void S2Length(auto v) { fS2Length = v; }
    void B2Radius(auto v) { fB2Radius = v; }
    void S3Length(auto v) { fS3Length = v; }
    void InnerRadius(auto v) { fInnerRadius = v; }
    void OuterRadius(auto v) { fOuterRadius = v; }
    void FieldRadius(auto v) { fFieldRadius = v; }

    // Next 5 methods should only use for geometry construction.

    HepGeom::Transform3D S1Transform() const;
    HepGeom::Transform3D B1Transform() const;
    HepGeom::Transform3D S2Transform() const;
    HepGeom::Transform3D B2Transform() const;
    HepGeom::Transform3D S3Transform() const;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    const auto& MagneticFluxDensity() const { return fMagneticFluxDensity; }

    void MagneticFluxDensity(auto v) { fMagneticFluxDensity = v; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    double fS1Length;
    double fB1Radius;
    double fS2Length;
    double fB2Radius;
    double fS3Length;
    double fInnerRadius;
    double fOuterRadius;
    double fFieldRadius;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    double fMagneticFluxDensity;
};

} // namespace MACE::Detector::Description
