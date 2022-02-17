#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::ThirdTransportSolenoid final :
    public MACE::Geometry::Interface::Description {
public:
    static ThirdTransportSolenoid& Instance() noexcept;

private:
    ThirdTransportSolenoid() noexcept = default;
    ~ThirdTransportSolenoid() noexcept = default;
    ThirdTransportSolenoid(const ThirdTransportSolenoid&) = delete;
    ThirdTransportSolenoid& operator=(const ThirdTransportSolenoid&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "ThirdTransportSolenoid"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return ""; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return ""; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return ""; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return ""; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetOuterRaidus() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetInnerRaidus() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetCenterX()     const { return fCenterX; }
    [[nodiscard]] const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fLength = 20_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 170_cm;
};
