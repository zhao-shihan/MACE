#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::VertexDetectorShield final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(VertexDetectorShield);
public:
    const char* GetName()                   const override { return "VertexDetectorShield"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetInnerRadius()  const { return fInnerRadius; }
    auto GetInnerLength()  const { return fInnerLength; }
    auto GetWindowRadius() const { return fWindowRadius; }
    auto GetThickness()    const { return fThickness; }
    auto GetCenterX()      const { return fCenterX; }
    auto GetUpZPosition()  const { return fUpZPosition; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fInnerRadius = 25_cm;
    double fInnerLength = 60_cm;
    double fWindowRadius = 16_cm;
    double fThickness = 5_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 190_cm;
};