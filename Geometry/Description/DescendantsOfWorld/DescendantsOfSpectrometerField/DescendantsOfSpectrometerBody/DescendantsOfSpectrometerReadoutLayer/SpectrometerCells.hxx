#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerCells final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerCells& Instance();

private:
    SpectrometerCells() noexcept {}
    ~SpectrometerCells() noexcept {}
    SpectrometerCells(const SpectrometerCells&) = delete;
    SpectrometerCells& operator=(const SpectrometerCells&) = delete;

public:
    const char* GetName()                   const override { return "SpectrometerCell"; }
    const char* GetOverallDescription()     const override { return "Sensitive cells of MWDC. The cell's full geometry includes sense wires, field wires, and readout volume, respectively. Fast geometry might exclude wires."; }
    const char* GetMaterialDescription()    const override { return "Gas: Same as mother's. Wires: respect to BESIII currently."; }
    const char* GetShapeDescription()       const override { return "Wire: Cylinders. Gas: A angular slice of tube."; }
    const char* GetMotherDescription()      const override { return "SpectrometerBody"; }
    const char* GetTranslationDescription() const override { return "Depending on the implementation."; }
    const char* GetRotationDescription()    const override { return "Depending on the implementation."; }

    const auto& GetSenseWireDiameter() const { return fSenseWireDiameter; }
    const auto& GetFieldWireDiameter() const { return fFieldWireDiameter; }

    void SetSenseWireDiameter(double val) { fSenseWireDiameter = val; }
    void SetFieldWireDiameter(double val) { fFieldWireDiameter = val; }

private:
    double fSenseWireDiameter = 25_um;
    double fFieldWireDiameter = 110_um;
};
