#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::FirstTransportSolenoid final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstTransportSolenoid& Instance() noexcept;

private:
    FirstTransportSolenoid() noexcept = default;
    ~FirstTransportSolenoid() noexcept = default;
    FirstTransportSolenoid(const FirstTransportSolenoid&) = delete;
    FirstTransportSolenoid& operator=(const FirstTransportSolenoid&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "FirstTransportSolenoid"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetOuterRaidus() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetInnerRaidus() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fLength = 20_cm;
    double fUpZPosition = 50_cm;
};
