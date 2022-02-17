#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SpectrometerShield final :
    public MACE::Geometry::Interface::Description {
public:
    static SpectrometerShield& Instance() noexcept;

private:
    SpectrometerShield() noexcept = default;
    ~SpectrometerShield() noexcept = default;
    SpectrometerShield(const SpectrometerShield&) = delete;
    SpectrometerShield& operator=(const SpectrometerShield&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "SpectrometerShield"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return ""; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return ""; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return ""; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return ""; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetInnerRadius()  const { return fInnerRadius; }
    [[nodiscard]] const auto& GetInnerLength()  const { return fInnerLength; }
    [[nodiscard]] const auto& GetWindowRadius() const { return fWindowRadius; }
    [[nodiscard]] const auto& GetThickness()    const { return fThickness; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fInnerRadius = 50_cm;
    double fInnerLength = 110_cm;
    double fWindowRadius = 16_cm;
    double fThickness = 5_cm;
};
