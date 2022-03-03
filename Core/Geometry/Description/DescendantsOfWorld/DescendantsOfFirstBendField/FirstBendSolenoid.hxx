#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::FirstBendSolenoid final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstBendSolenoid& Instance() noexcept;

private:
    FirstBendSolenoid() = default;
    ~FirstBendSolenoid() noexcept = default;
    FirstBendSolenoid(const FirstBendSolenoid&) = delete;
    FirstBendSolenoid& operator=(const FirstBendSolenoid&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "FirstBendSolenoid"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetOuterRaidus() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetInnerRaidus() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetBendRadius()  const { return fBendRadius; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fInnerRadius = 5_cm;
    double fOuterRadius = 10_cm;
    double fBendRadius = 50_cm;
};
