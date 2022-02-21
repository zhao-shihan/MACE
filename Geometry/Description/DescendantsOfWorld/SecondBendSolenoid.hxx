#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondBendSolenoid final :
    public MACE::Geometry::Interface::Description {
public:
    static SecondBendSolenoid& Instance() noexcept;

private:
    SecondBendSolenoid() noexcept = default;
    ~SecondBendSolenoid() noexcept = default;
    SecondBendSolenoid(const SecondBendSolenoid&) = delete;
    SecondBendSolenoid& operator=(const SecondBendSolenoid&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SecondBendSolenoid"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetOuterRaidus() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetInnerRaidus() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetBendRadius()  const { return fBendRadius; }
    [[nodiscard]] const auto& GetXPosition()   const { return fXPosition; }
    [[nodiscard]] const auto& GetZPosition()   const { return fZPosition; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetBendRadius(double val) { fBendRadius = val; }
    void SetXPosition(double val) { fXPosition = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fBendRadius = 50_cm;
    double fXPosition = 150_cm;
    double fZPosition = 170_cm;
};
