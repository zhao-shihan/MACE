#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerReadoutLayers final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerReadoutLayers& Instance() noexcept;

private:
    SpectrometerReadoutLayers() noexcept = default;
    ~SpectrometerReadoutLayers() noexcept = default;
    SpectrometerReadoutLayers(const SpectrometerReadoutLayers&) = delete;
    SpectrometerReadoutLayers& operator=(const SpectrometerReadoutLayers&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerReadoutLayer"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return "Readout layer of MWDC. Mother volume of cells and field wires."; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return "Helium based gas."; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return "Tube."; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return "SpectrometerBody"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetAverageCellWidth() const { return fAverageCellWidth; }

    void SetAverageCellWidth(double val) { fAverageCellWidth = val; }

private:
    double fAverageCellWidth = 1_cm;
};
