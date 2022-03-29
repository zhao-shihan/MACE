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
    std::string GetName() const override { return "Calorimeter"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetInnerLength() const { return fInnerLength; }
    const auto& GetWindowRadius() const { return fWindowRadius; }
    const auto& GetCrystalLength() const { return fCrystalLength; }

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
