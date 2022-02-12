#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondTransportSolenoid final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SecondTransportSolenoid);
public:
    const char* GetName()                   const override { return "SecondTransportSolenoid"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetOuterRaidus() const { return fOuterRadius; }
    const auto& GetInnerRaidus() const { return fInnerRadius; }
    const auto& GetLength()      const { return fLength; }
    const auto& GetCenterZ()     const { return fCenterZ; }
    const auto& GetUpXPosition() const { return fUpXPosition; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetCenterZ(double val) { fCenterZ = val; }
    void SetUpXPosition(double val) { fUpXPosition = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fLength = 100_cm;
    double fCenterZ = 120_cm;
    double fUpXPosition = 50_cm;
};