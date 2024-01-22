#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

namespace MACE::Detector::Description {

class Solenoid final : public DescriptionSingletonBase<Solenoid> {
    friend Env::Memory::SingletonInstantiator;

private:
    Solenoid();
    ~Solenoid() = default;

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    auto S1Length() const -> const auto& { return fS1Length; }
    auto B1Radius() const -> const auto& { return fB1Radius; }
    auto S2Length() const -> const auto& { return fS2Length; }
    auto B2Radius() const -> const auto& { return fB2Radius; }
    auto S3Length() const -> const auto& { return fS3Length; }
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto OuterRadius() const -> const auto& { return fOuterRadius; }
    auto FieldRadius() const -> const auto& { return fFieldRadius; }

    auto S1Length(auto v) -> void { fS1Length = v; }
    auto B1Radius(auto v) -> void { fB1Radius = v; }
    auto S2Length(auto v) -> void { fS2Length = v; }
    auto B2Radius(auto v) -> void { fB2Radius = v; }
    auto S3Length(auto v) -> void { fS3Length = v; }
    auto InnerRadius(auto v) -> void { fInnerRadius = v; }
    auto OuterRadius(auto v) -> void { fOuterRadius = v; }
    auto FieldRadius(auto v) -> void { fFieldRadius = v; }

    auto S1Center() const -> stdx::array3d { return {0, 0, (SpectrometerField::Instance().Length() + fS1Length) / 2}; }
    auto B1Center() const -> stdx::array3d { return S1Center() + stdx::array3d{fB1Radius, 0, fS1Length / 2}; }
    auto S2Center() const -> stdx::array3d { return B1Center() + stdx::array3d{fS2Length / 2, 0, fB1Radius}; }
    auto B2Center() const -> stdx::array3d { return S2Center() + stdx::array3d{fS2Length / 2, 0, fB2Radius}; }
    auto S3Center() const -> stdx::array3d { return B2Center() + stdx::array3d{fB2Radius, 0, fS3Length / 2}; }

    // // Next 5 methods should only use for geometry construction.

    // HepGeom::Transform3D S1Transform() const;
    // HepGeom::Transform3D B1Transform() const;
    // HepGeom::Transform3D S2Transform() const;
    // HepGeom::Transform3D B2Transform() const;
    // HepGeom::Transform3D S3Transform() const;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    const auto& MagneticFluxDensity() const { return fMagneticFluxDensity; }

    void MagneticFluxDensity(auto v) { fMagneticFluxDensity = v; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

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
