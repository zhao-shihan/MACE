#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class SpectrometerBody final : public IDescription {
public:
    static SpectrometerBody& Instance() noexcept;

private:
    SpectrometerBody() = default;
    ~SpectrometerBody() noexcept = default;
    SpectrometerBody(const SpectrometerBody&) = delete;
    SpectrometerBody& operator=(const SpectrometerBody&) = delete;

public:
    std::string GetName() const override { return "SpectrometerBody"; }
    std::string GetOverallDescription() const override { return "The shell of spectrometer, mother of cells."; }
    std::string GetMaterialDescription() const override { return "Carbon fiber."; }
    std::string GetShapeDescription() const override { return "A rotate trapezoid."; }
    std::string GetMotherDescription() const override { return "SpectrometerField"; }
    std::string GetTranslationDescription() const override { return "No translation."; }
    std::string GetRotationDescription() const override { return "No rotation."; }

    const auto& GetGasInnerRadius() const { return fGasInnerRadius; }
    const auto& GetGasOuterRadius() const { return fGasOuterRadius; }
    const auto& GetGasInnerLength() const { return fGasInnerLength; }
    const auto& GetGasOuterLength() const { return fGasOuterLength; }
    const auto& GetShellInnerThickness() const { return fShellInnerThickness; }
    const auto& GetShellSideThickness() const { return fShellSideThickness; }
    const auto& GetShellOuterThickness() const { return fShellOuterThickness; }

    void SetGasInnerRadius(double val) { fGasInnerRadius = val; }
    void SetGasOuterRadius(double val) { fGasOuterRadius = val; }
    void SetGasInnerLength(double val) { fGasInnerLength = val; }
    void SetGasOuterLength(double val) { fGasOuterLength = val; }
    void SetShellInnerThickness(double val) { fShellInnerThickness = val; }
    void SetShellSideThickness(double val) { fShellSideThickness = val; }
    void SetShellOuterThickness(double val) { fShellOuterThickness = val; }

private:
    double fGasInnerRadius = 15_cm;
    double fGasOuterRadius = 45_cm;
    double fGasInnerLength = 90_cm;
    double fGasOuterLength = 180_cm;
    double fShellInnerThickness = 1_mm;
    double fShellSideThickness = 5_mm;
    double fShellOuterThickness = 10_mm;
};

} // namespace MACE::Geometry::Description
