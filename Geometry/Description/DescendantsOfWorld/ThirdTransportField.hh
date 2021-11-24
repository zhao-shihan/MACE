#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::ThirdTransportField final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(ThirdTransportField);
public:
    const char* GetName()                   const override { return "ThirdTransportField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetLength()      const { return fLength; }
    auto GetRadius()      const { return fRadius; }
    auto GetCenterX()     const { return fCenterX; }
    auto GetUpZPosition() const { return fUpZPosition; }

    void SetLength(double val) { fLength = val; }
    void SetRadius(double val) { fRadius = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fLength = 20_cm;
    double fRadius = 10_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 170_cm;
};