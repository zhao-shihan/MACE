#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondBendField final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SecondBendField);
public:
    const char* GetName()                   const override { return "SecondBendField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetRaidus()     const { return fRadius; }
    auto GetBendRadius() const { return fBendRadius; }
    auto GetXPosition()  const { return fXPosition; }
    auto GetZPosition()  const { return fZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }
    void SetXPosition(double val) { fXPosition = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 10_cm;
    double fBendRadius = 50_cm;
    double fXPosition = 150_cm;
    double fZPosition = 170_cm;
};