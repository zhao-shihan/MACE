#pragma once

#include "Core/Geometry/Description/CalorimeterField.hxx"

namespace MACE::Geometry::Description {

class CalorimeterShield final : public IDescription {
public:
    static CalorimeterShield& Instance() noexcept;

private:
    CalorimeterShield() = default;
    ~CalorimeterShield() noexcept = default;
    CalorimeterShield(const CalorimeterShield&) = delete;
    CalorimeterShield& operator=(const CalorimeterShield&) = delete;

public:
    std::string GetName() const override { return "CalorimeterShield"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetInnerLength() const { return fInnerLength; }
    const auto& GetWindowRadius() const { return fWindowRadius; }
    const auto& GetThickness() const { return fThickness; }
    auto GetTransform() const { return CalorimeterField::Instance().GetTransform(); }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fInnerRadius = 30_cm;
    double fInnerLength = 80_cm;
    double fWindowRadius = 12.7_cm;
    double fThickness = 5_cm;
};

} // namespace MACE::Geometry::Description
