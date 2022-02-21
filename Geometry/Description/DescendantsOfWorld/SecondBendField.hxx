#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondBendField final :
    public MACE::Geometry::Interface::Description {
public:
    static SecondBendField& Instance() noexcept;

private:
    SecondBendField() noexcept = default;
    ~SecondBendField() noexcept = default;
    SecondBendField(const SecondBendField&) = delete;
    SecondBendField& operator=(const SecondBendField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SecondBendField"; }
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
    double fXPosition = 150_cm;
    double fZPosition = 170_cm;
};
