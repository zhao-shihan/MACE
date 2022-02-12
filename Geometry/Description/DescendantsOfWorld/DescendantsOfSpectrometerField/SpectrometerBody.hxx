#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerBody final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SpectrometerBody);
public:
    const char* GetName()                   const override { return "SpectrometerBody"; }
    const char* GetOverallDescription()     const override { return "The shell of spectrometer, mother of cells."; }
    const char* GetMaterialDescription()    const override { return "Carbon fiber."; }
    const char* GetShapeDescription()       const override { return "A rotate trapezoid."; }
    const char* GetMotherDescription()      const override { return "SpectrometerField"; }
    const char* GetTranslationDescription() const override { return "No translation."; }
    const char* GetRotationDescription()    const override { return "No rotation."; }

    const auto& GetGasInnerRadius() const { return fGasInnerRadius; }
    const auto& GetGasOuterRadius() const { return fGasOuterRadius; }
    const auto& GetGasInnerLength() const { return fGasInnerLength; }
    const auto& GetGasOuterLength() const { return fGasOuterLength; }
    const auto& GetShellInnerThickness() const { return fShellInnerThickness; }
    const auto& GetShellSideThickness()  const { return fShellSideThickness; }
    const auto& GetShellOuterThickness() const { return fShellOuterThickness; }

    void SetGasInnerRadius(double val) { fGasInnerRadius = val; }
    void SetGasOuterRadius(double val) { fGasOuterRadius = val; }
    void SetGasInnerLength(double val) { fGasInnerLength = val; }
    void SetGasOuterLength(double val) { fGasOuterLength = val; }
    void SetShellInnerThickness(double val) { fShellInnerThickness = val; }
    void SetShellSideThickness(double val) { fShellSideThickness = val; }
    void SetShellOuterThickness(double val) { fShellOuterThickness = val; }

private:
    double fGasInnerRadius = 8_cm;
    double fGasOuterRadius = 32_cm;
    double fGasInnerLength = 39_cm;
    double fGasOuterLength = 81_cm;
    double fShellInnerThickness = 1_mm;
    double fShellSideThickness = 5_mm;
    double fShellOuterThickness = 10_mm;
};