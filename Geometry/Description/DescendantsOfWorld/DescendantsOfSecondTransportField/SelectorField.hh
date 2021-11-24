#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::SelectorField final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SelectorField);
public:
    const char* GetName()                   const override { return "SelectorField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetRaidus()    const { return fRadius; }
    auto GetLength()    const { return fLength; }
    auto GetZPosition() const { return fZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 10_cm;
    double fLength = 30_cm;
    double fZPosition = 20_cm;
};