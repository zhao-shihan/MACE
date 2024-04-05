#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

#include <string>
#include <utility>

namespace MACE::Detector::Description {

class Solenoid final : public DescriptionBase<Solenoid> {
    friend Env::Memory::SingletonInstantiator;

private:
    Solenoid();
    ~Solenoid() = default;

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    auto S1Length() const -> auto { return fS1Length; }
    auto B1Radius() const -> auto { return fB1Radius; }
    auto S2Length() const -> auto { return fS2Length; }
    auto B2Radius() const -> auto { return fB2Radius; }
    auto S3Length() const -> auto { return fS3Length; }
    auto InnerRadius() const -> auto { return fInnerRadius; }
    auto OuterRadius() const -> auto { return fOuterRadius; }
    auto FieldRadius() const -> auto { return fFieldRadius; }

    auto S1Length(double val) -> void { fS1Length = val; }
    auto B1Radius(double val) -> void { fB1Radius = val; }
    auto S2Length(double val) -> void { fS2Length = val; }
    auto B2Radius(double val) -> void { fB2Radius = val; }
    auto S3Length(double val) -> void { fS3Length = val; }
    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto OuterRadius(double val) -> void { fOuterRadius = val; }
    auto FieldRadius(double val) -> void { fFieldRadius = val; }

    auto S1Center() const -> stdx::array3d { return {0, 0, (MMSField::Instance().Length() + fS1Length) / 2}; }
    auto B1Center() const -> stdx::array3d { return S1Center() + stdx::array3d{fB1Radius, 0, fS1Length / 2}; }
    auto S2Center() const -> stdx::array3d { return B1Center() + stdx::array3d{fS2Length / 2, 0, fB1Radius}; }
    auto B2Center() const -> stdx::array3d { return S2Center() + stdx::array3d{fS2Length / 2, 0, fB2Radius}; }
    auto S3Center() const -> stdx::array3d { return B2Center() + stdx::array3d{fB2Radius, 0, fS3Length / 2}; }

    ///////////////////////////////////////////////////////////
    // Material
    ///////////////////////////////////////////////////////////

    auto MaterialName() const -> const auto& { return fMaterialName; }

    auto MaterialName(std::string val) -> void { fMaterialName = std::move(val); }

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    const auto& MagneticFluxDensity() const { return fMagneticFluxDensity; }

    void MagneticFluxDensity(auto v) { fMagneticFluxDensity = v; }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

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
    // Material
    ///////////////////////////////////////////////////////////

    std::string fMaterialName;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    double fMagneticFluxDensity;
};

} // namespace MACE::Detector::Description
