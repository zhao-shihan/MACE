#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::FirstBendSolenoid final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(FirstBendSolenoid);
public:
    const char* GetName()                   const override { return "FirstBendSolenoid"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetOuterRaidus() const { return fOuterRadius; }
    auto GetInnerRaidus() const { return fInnerRadius; }
    auto GetBendRadius()  const { return fBendRadius; }
    auto GetXPosition()   const { return fXPosition; }
    auto GetZPosition()   const { return fZPosition; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }
    void SetXPosition(double val) { fXPosition = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fBendRadius = 50_cm;
    double fXPosition = fBendRadius;
    double fZPosition = 70_cm;
};