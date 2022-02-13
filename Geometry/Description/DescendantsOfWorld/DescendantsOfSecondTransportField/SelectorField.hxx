#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SelectorField final :
    public MACE::Geometry::Interface::Description {
public:
    static SelectorField& Instance();

private:
    SelectorField() noexcept {}
    ~SelectorField() noexcept {}
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

public:
    const char* GetName()                   const override { return "SelectorField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetRaidus()    const { return fRadius; }
    const auto& GetLength()    const { return fLength; }
    const auto& GetZPosition() const { return fZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 10_cm;
    double fLength = 30_cm;
    double fZPosition = 20_cm;
};
