#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::ThirdTransportSolenoid final :
    public MACE::Geometry::Interface::Description {
public:
    static ThirdTransportSolenoid& Instance() noexcept;

private:
    ThirdTransportSolenoid() = default;
    ~ThirdTransportSolenoid() noexcept = default;
    ThirdTransportSolenoid(const ThirdTransportSolenoid&) = delete;
    ThirdTransportSolenoid& operator=(const ThirdTransportSolenoid&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "ThirdTransportSolenoid"; }
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
    double fInnerRadius = 7.5_cm;
    double fOuterRadius = 12.5_cm;
    double fLength = 20_cm;
};
