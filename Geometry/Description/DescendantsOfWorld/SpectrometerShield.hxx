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
    [[nodiscard]] std::string GetName()                   const override { return "SpectrometerShield"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

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
