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
    const char* GetName()                   const override { return "SpectrometerReadoutLayer"; }
    const char* GetOverallDescription()     const override { return "Readout layer of MWDC. Cell's mother."; }
    const char* GetMaterialDescription()    const override { return "Helium based gas."; }
    const char* GetShapeDescription()       const override { return "Tube."; }
    const char* GetMotherDescription()      const override { return "SpectrometerBody"; }
    const char* GetTranslationDescription() const override { return "No translation."; }
    const char* GetRotationDescription()    const override { return "No rotation."; }

    const auto& GetAverageCellWidth() const { return fAverageCellWidth; }

    void SetAverageCellWidth(double val) { fAverageCellWidth = val; }

private:
    double fAverageCellWidth = 1_cm;
};
