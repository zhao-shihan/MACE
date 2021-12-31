#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondTransportField final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SecondTransportField);
public:
    const char* GetName()                   const override { return "SecondTransportField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetLength()      const { return fLength; }
    auto GetRadius()      const { return fRadius; }
    auto GetCenterZ()     const { return fCenterZ; }
    auto GetUpXPosition() const { return fUpXPosition; }

    void SetLength(double val) { fLength = val; }
    void SetRadius(double val) { fRadius = val; }
    void SetCenterZ(double val) { fCenterZ = val; }
    void SetUpXPosition(double val) { fUpXPosition = val; }

private:
    double fLength = 100_cm;
    double fRadius = 10_cm;
    double fCenterZ = 120_cm;
    double fUpXPosition = 50_cm;
};