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
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerCell"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return "Sensitive cells of MWDC. The cell's full geometry includes sense wires, field wires, and readout volume, respectively. Fast geometry might exclude wires."; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return "Gas: Same as mother's. Wires: respect to BESIII currently."; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return "Wire: Cylinders. Gas: A angular slice of tube."; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return "SpectrometerBody"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "Depending on the implementation."; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return "Depending on the implementation."; }

    [[nodiscard]] const auto& GetSenseWireDiameter() const { return fSenseWireDiameter; }
    [[nodiscard]] const auto& GetFieldWireDiameter() const { return fFieldWireDiameter; }

    void SetSenseWireDiameter(double val) { fSenseWireDiameter = val; }
    void SetFieldWireDiameter(double val) { fFieldWireDiameter = val; }

private:
    double fSenseWireDiameter = 25_um;
    double fFieldWireDiameter = 110_um;
};
