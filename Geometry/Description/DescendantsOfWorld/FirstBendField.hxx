#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::FirstBendField final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstBendField& Instance();

private:
    FirstBendField() noexcept {}
    ~FirstBendField() noexcept {}
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

public:
    const char* GetName()                   const override { return "FirstBendField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetRaidus()     const { return fRadius; }
    const auto& GetBendRadius() const { return fBendRadius; }
    const auto& GetXPosition()  const { return fXPosition; }
    const auto& GetZPosition()  const { return fZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }
    void SetXPosition(double val) { fXPosition = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 10_cm;
    double fBendRadius = 50_cm;
    double fXPosition = fBendRadius;
    double fZPosition = 70_cm;
};
