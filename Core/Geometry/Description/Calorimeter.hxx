#pragma once

#include "Geometry/Description/IDescription.hxx"

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
    [[nodiscard]] const auto& GetOuterRadius() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetLength() const { return fLength; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fInnerRadius = 15_cm;
    double fOuterRadius = 20_cm;
    double fLength = 40_cm;
};

} // namespace MACE::Geometry::Description
