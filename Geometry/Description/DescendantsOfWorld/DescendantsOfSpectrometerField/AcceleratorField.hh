#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::AcceleratorField final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(AcceleratorField);
public:
    const char* GetName()                   const override { return "AcceleratorField"; }
    const char* GetOverallDescription()     const override { return "An accelerator field box inside spectrometer"; }
    const char* GetMaterialDescription()    const override { return "Vacuum."; }
    const char* GetShapeDescription()       const override { return "A box with certain Width(along XY), UpStreamLength(length of z<0), and DownStreamLength(length of z>0)."; }
    const char* GetMotherDescription()      const override { return "SpectrometerField"; }
    const char* GetTranslationDescription() const override { return "Translation should ensure the center z position satisifies shape description (see above)."; }
    const char* GetRotationDescription()    const override { return "No rotation."; }

    auto GetWidth() { return fWidth; }
    auto GetUpStreamLength() { return fUpStreamLength; }
    auto GetDownStreamLength() { return fDownStreamLength; }

    void SetWidth(double val) { fWidth = val; }
    void SetUpStreamLength(double val) { fUpStreamLength = val; }
    void SetDownStreamLength(double val) { fDownStreamLength = val; }

private:
    double fWidth = M_SQRT2 * 7_cm;
    double fUpStreamLength = 4_cm;
    double fDownStreamLength = 30_cm;
};