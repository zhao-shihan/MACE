#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::SpectrometerShell final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SpectrometerShell);
public:
    const char* GetName()                   const override { return "SpectrometerShell"; }
    const char* GetOverallDescription()     const override { return "The shell of spectrometer."; }
    const char* GetMaterialDescription()    const override { return "Carbon fiber."; }
    const char* GetShapeDescription()       const override { return "A rotate trapezoid."; }
    const char* GetMotherDescription()      const override { return "SpectrometerField"; }
    const char* GetTranslationDescription() const override { return "No translation."; }
    const char* GetRotationDescription()    const override { return "No rotation."; }

    auto GetInnerRadius()    const { return fGasInnerRadius; }
    auto GetOuterRadius()    const { return fGasOuterRadius; }
    auto GetInnerLength()    const { return fGasInnerLength; }
    auto GetOuterLength()    const { return fGasOuterLength; }
    auto GetInnerThickness() const { return  fShellInnerThickness; }
    auto GetSideThickness()  const { return fShellSideThickness; }
    auto GetOuterThickness() const { return  fShellOuterThickness; }

    void SetInnerRadius(double val) { fGasInnerRadius = val; }
    void SetOuterRadius(double val) { fGasOuterRadius = val; }
    void SetInnerLength(double val) { fGasInnerLength = val; }
    void SetOuterLength(double val) { fGasOuterLength = val; }
    void SetInnerThickness(double val) { fShellInnerThickness = val; }
    void SetSideThickness(double val) { fShellSideThickness = val; }
    void SetOuterThickness(double val) { fShellOuterThickness = val; }

private:
    double fGasInnerRadius = 8_cm;
    double fGasOuterRadius = 32_cm;
    double fGasInnerLength = 39_cm;
    double fGasOuterLength = 81_cm;
    double fShellInnerThickness = 1_mm;
    double fShellSideThickness = 5_mm;
    double fShellOuterThickness = 10_mm;
};