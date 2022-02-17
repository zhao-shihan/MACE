#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerReadoutLayer final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerReadoutLayer& Instance() noexcept;

private:
    SpectrometerReadoutLayer() noexcept = default;
    ~SpectrometerReadoutLayer() noexcept = default;
    SpectrometerReadoutLayer(const SpectrometerReadoutLayer&) = delete;
    SpectrometerReadoutLayer& operator=(const SpectrometerReadoutLayer&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "SpectrometerReadoutLayer"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return "Readout layer of MWDC. Cell's mother."; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return "Helium based gas."; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return "Tube."; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return "SpectrometerBody"; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetAverageCellWidth() const { return fAverageCellWidth; }

    void SetAverageCellWidth(double val) { fAverageCellWidth = val; }

private:
    double fAverageCellWidth = 1_cm;
};
