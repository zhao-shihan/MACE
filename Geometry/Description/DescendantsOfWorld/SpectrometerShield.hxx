#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerShield final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SpectrometerShield);
public:
    const char* GetName()                   const override { return "SpectrometerShield"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetInnerRadius()  const { return fInnerRadius; }
    auto GetInnerLength()  const { return fInnerLength; }
    auto GetWindowRadius() const { return fWindowRadius; }
    auto GetThickness()    const { return fThickness; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fInnerRadius = 50_cm;
    double fInnerLength = 110_cm;
    double fWindowRadius = 11_cm;
    double fThickness = 5_cm;
};