#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondTransportSolenoid final :
    public MACE::Geometry::Interface::Description {
public:
    static SecondTransportSolenoid& Instance() noexcept;

private:
    SecondTransportSolenoid() noexcept = default;
    ~SecondTransportSolenoid() noexcept = default;
    SecondTransportSolenoid(const SecondTransportSolenoid&) = delete;
    SecondTransportSolenoid& operator=(const SecondTransportSolenoid&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SecondTransportSolenoid"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetOuterRaidus() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetInnerRaidus() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetLength()      const { return fLength; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fLength = 100_cm;
};
