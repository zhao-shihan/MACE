#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::Calorimeter final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(Calorimeter);
public:
    const char* GetName()                   const override { return "Calorimeter"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetInnerRadius() { return fInnerRadius; }
    auto GetOuterRadius() { return fOuterRadius; }
    auto GetLength() { return fLength; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fInnerRadius = 8.5_cm;
    double fOuterRadius = 14.5_cm;
    double fLength = 28_cm;
};