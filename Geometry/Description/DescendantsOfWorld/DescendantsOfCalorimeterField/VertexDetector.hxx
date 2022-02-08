#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::VertexDetector final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(VertexDetector);
public:
    const char* GetName()                   const override { return "VertexDetector"; }
    const char* GetOverallDescription()     const override { return ""; }
    const char* GetMaterialDescription()    const override { return ""; }
    const char* GetShapeDescription()       const override { return ""; }
    const char* GetMotherDescription()      const override { return ""; }
    const char* GetTranslationDescription() const override { return ""; }
    const char* GetRotationDescription()    const override { return ""; }

    auto GetWidth()     const { return fWidth; }
    auto GetThickness() const { return fThickness; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fWidth = 10_cm;
    double fThickness = 1_cm;
};