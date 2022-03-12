#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerBody final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerBody& Instance() noexcept;

private:
    SpectrometerBody() = default;
    ~SpectrometerBody() noexcept = default;
    SpectrometerBody(const SpectrometerBody&) = delete;
    SpectrometerBody& operator=(const SpectrometerBody&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerBody"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return "The shell of spectrometer, mother of cells."; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return "Carbon fiber."; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return "A rotate trapezoid."; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return "SpectrometerField"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetGasInnerRadius() const { return fGasInnerRadius; }
    [[nodiscard]] const auto& GetGasOuterRadius() const { return fGasOuterRadius; }
    [[nodiscard]] const auto& GetGasInnerLength() const { return fGasInnerLength; }
    [[nodiscard]] const auto& GetGasOuterLength() const { return fGasOuterLength; }
    [[nodiscard]] const auto& GetShellInnerThickness() const { return fShellInnerThickness; }
    [[nodiscard]] const auto& GetShellSideThickness()  const { return fShellSideThickness; }
    [[nodiscard]] const auto& GetShellOuterThickness() const { return fShellOuterThickness; }

    void SetGasInnerRadius(double val) { fGasInnerRadius = val; }
    void SetGasOuterRadius(double val) { fGasOuterRadius = val; }
    void SetGasInnerLength(double val) { fGasInnerLength = val; }
    void SetGasOuterLength(double val) { fGasOuterLength = val; }
    void SetShellInnerThickness(double val) { fShellInnerThickness = val; }
    void SetShellSideThickness(double val) { fShellSideThickness = val; }
    void SetShellOuterThickness(double val) { fShellOuterThickness = val; }

private:
    double fGasInnerRadius = 15_cm;
    double fGasOuterRadius = 50_cm;
    double fGasInnerLength = 90_cm;
    double fGasOuterLength = 200_cm;
    double fShellInnerThickness = 1_mm;
    double fShellSideThickness = 5_mm;
    double fShellOuterThickness = 10_mm;
};
