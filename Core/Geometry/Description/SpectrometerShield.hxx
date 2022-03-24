#pragma once

#include "Geometry/Description/IDescription.hxx"

namespace MACE::Geometry::Description {

class SpectrometerShield final : public IDescription {
public:
    static SpectrometerShield& Instance() noexcept;

private:
    SpectrometerShield() = default;
    ~SpectrometerShield() noexcept = default;
    SpectrometerShield(const SpectrometerShield&) = delete;
    SpectrometerShield& operator=(const SpectrometerShield&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "SpectrometerShield"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetInnerRadius() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetInnerLength() const { return fInnerLength; }
    [[nodiscard]] const auto& GetWindowRadius() const { return fWindowRadius; }
    [[nodiscard]] const auto& GetThickness() const { return fThickness; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fInnerRadius = 72_cm;
    double fInnerLength = 222_cm;
    double fWindowRadius = 12.7_cm;
    double fThickness = 5_cm;
};

} // namespace MACE::Geometry::Description
