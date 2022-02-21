#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::CalorimeterField final :
    public MACE::Geometry::Interface::Description {
public:
    static CalorimeterField& Instance() noexcept;

private:
    CalorimeterField() noexcept = default;
    ~CalorimeterField() noexcept = default;
    CalorimeterField(const CalorimeterField&) = delete;
    CalorimeterField& operator=(const CalorimeterField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "CalorimeterField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRadius()      const { return fRadius; }
    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetCenterX()     const { return fCenterX; }
    [[nodiscard]] const auto& GetUpZPosition() const { return fUpZPosition; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fRadius = 23_cm;
    double fLength = 50_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 190_cm;
};
