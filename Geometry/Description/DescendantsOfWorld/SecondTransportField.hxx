#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SecondTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static SecondTransportField& Instance() noexcept;

private:
    SecondTransportField() noexcept = default;
    ~SecondTransportField() noexcept = default;
    SecondTransportField(const SecondTransportField&) = delete;
    SecondTransportField& operator=(const SecondTransportField&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "SecondTransportField"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return ""; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return ""; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return ""; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return ""; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetRadius()      const { return fRadius; }
    [[nodiscard]] const auto& GetCenterZ()     const { return fCenterZ; }
    [[nodiscard]] const auto& GetUpXPosition() const { return fUpXPosition; }

    void SetLength(double val) { fLength = val; }
    void SetRadius(double val) { fRadius = val; }
    void SetCenterZ(double val) { fCenterZ = val; }
    void SetUpXPosition(double val) { fUpXPosition = val; }

private:
    double fLength = 100_cm;
    double fRadius = 10_cm;
    double fCenterZ = 120_cm;
    double fUpXPosition = 50_cm;
};
