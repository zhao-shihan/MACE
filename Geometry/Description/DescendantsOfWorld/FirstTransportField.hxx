#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::FirstTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstTransportField& Instance() noexcept;

private:
    FirstTransportField() noexcept = default;
    ~FirstTransportField() noexcept = default;
    FirstTransportField(const FirstTransportField&) = delete;
    FirstTransportField& operator=(const FirstTransportField&) = delete;

public:
    const char* GetName()                   const override { return "FirstTransportField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetRaidus()      const { return fRadius; }
    const auto& GetLength()      const { return fLength; }
    const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fRadius = 10_cm;
    double fLength = 20_cm;
    double fUpZPosition = 50_cm;
};
