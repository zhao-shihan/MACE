#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerReadoutLayer final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SpectrometerReadoutLayer);
public:
    const char* GetName()                   const override { return "SpectrometerReadoutLayer"; }
    const char* GetOverallDescription()     const override { return "Readout layer of MWDC. Cell's mother."; }
    const char* GetMaterialDescription()    const override { return "Helium based gas."; }
    const char* GetShapeDescription()       const override { return "Tube."; }
    const char* GetMotherDescription()      const override { return "SpectrometerBody"; }
    const char* GetTranslationDescription() const override { return "No translation."; }
    const char* GetRotationDescription()    const override { return "No rotation."; }

    auto GetLayerThickness() const { return fLayerThickness; }

    void SetLayerThickness(double val) { fLayerThickness = val; }

private:
    double fLayerThickness = 1_cm;
};