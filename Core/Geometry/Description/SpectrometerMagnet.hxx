#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class SpectrometerMagnet final : public IDescription {
public:
    static SpectrometerMagnet& Instance() noexcept;

private:
    SpectrometerMagnet() = default;
    ~SpectrometerMagnet() noexcept = default;
    SpectrometerMagnet(const SpectrometerMagnet&) = delete;
    SpectrometerMagnet& operator=(const SpectrometerMagnet&) = delete;

public:
    std::string GetName() const override { return "SpectrometerMagnet"; }
    std::string GetOverallDescription() const override { return "The magnet of spectrometer."; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return "G4Tubs."; }
    std::string GetMotherDescription() const override { return "SpectrometerField"; }
    std::string GetTranslationDescription() const override { return "No translation."; }
    std::string GetRotationDescription() const override { return "No rotation."; }

    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetOuterRadius() const { return fOuterRadius; }
    const auto& GetLength() const { return fLength; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fInnerRadius = 50_cm;
    double fOuterRadius = 70_cm;
    double fLength = 218_cm;
};

} // namespace MACE::Geometry::Description
