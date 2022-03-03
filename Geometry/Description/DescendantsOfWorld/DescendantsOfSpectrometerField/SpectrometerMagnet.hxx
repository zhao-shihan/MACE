#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerMagnet final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerMagnet& Instance() noexcept;

private:
    SpectrometerMagnet() = default;
    ~SpectrometerMagnet() noexcept = default;
    SpectrometerMagnet(const SpectrometerMagnet&) = delete;
    SpectrometerMagnet& operator=(const SpectrometerMagnet&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerMagnet"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return "The magnet of spectrometer."; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return "G4Tubs."; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return "SpectrometerField"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetInnerRadius() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetOuterRadius() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetLength() const { return fLength; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fInnerRadius = 32_cm;
    double fOuterRadius = 48_cm;
    double fLength = 180_cm;
};
