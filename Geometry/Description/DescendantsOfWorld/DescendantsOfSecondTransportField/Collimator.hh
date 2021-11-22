#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::Collimator final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(Collimator);
public:
    const char* GetName()                   const override { return "Collimator"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetInnerRadius() { return fInnerRadius; }
    auto GetOuterRadius() { return fOuterRadius; }
    auto GetThickness() { return fThickness; }
    auto GetZPosition() { return fZPosition; }
    auto GetCount() { return fCount; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetZPosition(double val) { fZPosition = val; }
    void SetCount(int val) { fCount = val; }

private:
    double fInnerRadius = 5_mm;
    double fOuterRadius = 75_mm;
    double fLength = 30_cm;
    double fZPosition = -20_cm;
    double fThickness = 1_mm;
    int fCount = 5;
};