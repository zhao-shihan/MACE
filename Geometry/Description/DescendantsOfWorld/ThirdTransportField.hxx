#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::ThirdTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static ThirdTransportField& Instance() noexcept;

private:
    ThirdTransportField() noexcept = default;
    ~ThirdTransportField() noexcept = default;
    ThirdTransportField(const ThirdTransportField&) = delete;
    ThirdTransportField& operator=(const ThirdTransportField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "ThirdTransportField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetRadius()      const { return fRadius; }
    [[nodiscard]] const auto& GetCenterX()     const { return fCenterX; }
    [[nodiscard]] const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetLength(double val) { fLength = val; }
    void SetRadius(double val) { fRadius = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fLength = 20_cm;
    double fRadius = 16_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 170_cm;
};
