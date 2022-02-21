#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::FirstTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstTransportField& Instance() noexcept;

private:
    FirstTransportField() noexcept = default;
    ~FirstTransportField() noexcept = default;
    FirstTransportField(const FirstTransportField&) = delete;
    FirstTransportField& operator=(const FirstTransportField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "FirstTransportField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRaidus()      const { return fRadius; }
    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fRadius = 10_cm;
    double fLength = 20_cm;
    double fUpZPosition = 50_cm;
};
