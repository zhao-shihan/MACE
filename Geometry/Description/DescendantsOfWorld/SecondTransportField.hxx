#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static SecondTransportField& Instance();

private:
    SecondTransportField() noexcept {}
    ~SecondTransportField() noexcept {}
    SecondTransportField(const SecondTransportField&) = delete;
    SecondTransportField& operator=(const SecondTransportField&) = delete;

public:
    const char* GetName()                   const override { return "SecondTransportField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetLength()      const { return fLength; }
    const auto& GetRadius()      const { return fRadius; }
    const auto& GetCenterZ()     const { return fCenterZ; }
    const auto& GetUpXPosition() const { return fUpXPosition; }

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
