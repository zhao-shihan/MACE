#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::FirstBendField final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstBendField& Instance() noexcept;

private:
    FirstBendField() noexcept = default;
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "FirstBendField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRaidus()     const { return fRadius; }
    [[nodiscard]] const auto& GetBendRadius() const { return fBendRadius; }
    [[nodiscard]] const auto& GetXPosition()  const { return fXPosition; }
    [[nodiscard]] const auto& GetZPosition()  const { return fZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }
    void SetXPosition(double val) { fXPosition = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 10_cm;
    double fBendRadius = 50_cm;
    double fXPosition = fBendRadius;
    double fZPosition = 70_cm;
};
