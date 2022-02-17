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
    [[nodiscard]] const char* GetName()                   const override { return "SecondTransportSolenoid"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return ""; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return ""; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return ""; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return ""; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetOuterRaidus() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetInnerRaidus() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetCenterZ()     const { return fCenterZ; }
    [[nodiscard]] const auto& GetUpXPosition() const { return fUpXPosition; }

    void SetOuterRaidus(double val) { fInnerRadius = val; }
    void SetInnerRaidus(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetCenterZ(double val) { fCenterZ = val; }
    void SetUpXPosition(double val) { fUpXPosition = val; }

private:
    double fInnerRadius = 10_cm;
    double fOuterRadius = 15_cm;
    double fLength = 100_cm;
    double fCenterZ = 120_cm;
    double fUpXPosition = 50_cm;
};
