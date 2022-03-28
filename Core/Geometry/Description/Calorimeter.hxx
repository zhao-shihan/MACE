#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class Calorimeter final : public IDescription {
public:
    static Calorimeter& Instance() noexcept;

private:
    Calorimeter() = default;
    ~Calorimeter() noexcept = default;
    Calorimeter(const Calorimeter&) = delete;
    Calorimeter& operator=(const Calorimeter&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "Calorimeter"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetInnerRadius() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetInnerLength() const { return fInnerLength; }
    [[nodiscard]] const auto& GetWindowRadius() const { return fWindowRadius; }
    [[nodiscard]] const auto& GetCrystalLength() const { return fCrystalLength; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetCrystalLength(double val) { fCrystalLength = val; }

private:
    double fInnerRadius = 15_cm;
    double fInnerLength = 50_cm;
    double fWindowRadius = 8_cm;
    double fCrystalLength = 5_cm;
};

} // namespace MACE::Geometry::Description
