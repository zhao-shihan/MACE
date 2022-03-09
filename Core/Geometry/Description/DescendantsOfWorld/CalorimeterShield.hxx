#pragma once

#include "Geometry/Description/DescendantsOfWorld/CalorimeterField.hxx"

class MACE::Geometry::Description::CalorimeterShield final :
    public MACE::Geometry::Interface::Description {
public:
    static CalorimeterShield& Instance() noexcept;

private:
    CalorimeterShield() = default;
    ~CalorimeterShield() noexcept = default;
    CalorimeterShield(const CalorimeterShield&) = delete;
    CalorimeterShield& operator=(const CalorimeterShield&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "CalorimeterShield"; }
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
    [[nodiscard]] auto        GetTransform()    const { return CalorimeterField::Instance().GetTransform(); }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fInnerRadius = 25_cm;
    double fInnerLength = 60_cm;
    double fWindowRadius = 12.7_cm;
    double fThickness = 5_cm;
};
