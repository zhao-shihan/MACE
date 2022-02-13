#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::CalorimeterField final :
    public MACE::Geometry::Interface::Description {
public:
    static CalorimeterField& Instance();

private:
    CalorimeterField() noexcept {}
    ~CalorimeterField() noexcept {}
    CalorimeterField(const CalorimeterField&) = delete;
    CalorimeterField& operator=(const CalorimeterField&) = delete;

public:
    const char* GetName()                   const override { return "CalorimeterField"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    const auto& GetRadius()      const { return fRadius; }
    const auto& GetLength()      const { return fLength; }
    const auto& GetCenterX()     const { return fCenterX; }
    const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fRadius = 23_cm;
    double fLength = 50_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 190_cm;
};
