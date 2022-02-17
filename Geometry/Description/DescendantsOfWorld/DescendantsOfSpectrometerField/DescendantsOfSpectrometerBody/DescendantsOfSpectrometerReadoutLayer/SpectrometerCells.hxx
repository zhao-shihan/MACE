#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerCells final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerCells& Instance() noexcept;

private:
    SpectrometerCells() noexcept = default;
    ~SpectrometerCells() noexcept = default;
    SpectrometerCells(const SpectrometerCells&) = delete;
    SpectrometerCells& operator=(const SpectrometerCells&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "SpectrometerCell"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return "Sensitive cells of MWDC. The cell's full geometry includes sense wires, field wires, and readout volume, respectively. Fast geometry might exclude wires."; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return "Gas: Same as mother's. Wires: respect to BESIII currently."; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return "Wire: Cylinders. Gas: A angular slice of tube."; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return "SpectrometerBody"; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return "Depending on the implementation."; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return "Depending on the implementation."; }

    [[nodiscard]] const auto& GetSenseWireDiameter() const { return fSenseWireDiameter; }
    [[nodiscard]] const auto& GetFieldWireDiameter() const { return fFieldWireDiameter; }

    void SetSenseWireDiameter(double val) { fSenseWireDiameter = val; }
    void SetFieldWireDiameter(double val) { fFieldWireDiameter = val; }

private:
    double fSenseWireDiameter = 25_um;
    double fFieldWireDiameter = 110_um;
};
