#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerField final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerField& Instance();

private:
    SpectrometerField() noexcept {}
    ~SpectrometerField() noexcept {}
    SpectrometerField(const SpectrometerField&) = delete;
    SpectrometerField& operator=(const SpectrometerField&) = delete;

public:
    const char* GetName()                   const override { return "SpectrometerField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 37_cm;
    double fLength = 100_cm;
};
