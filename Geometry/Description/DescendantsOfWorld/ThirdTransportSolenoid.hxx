#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::ThirdTransportSolenoid final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(ThirdTransportSolenoid);
public:
    const char* GetName()                   const override { return "ThirdTransportSolenoid"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetOuterRaidus() const { return fOuterRadius; }
    const auto& GetInnerRaidus() const { return fInnerRadius; }
    const auto& GetLength()      const { return fLength; }
    const auto& GetCenterX()     const { return fCenterX; }
    const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fLength = 20_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 170_cm;
};