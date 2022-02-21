#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::VertexDetectorShield final :
    public MACE::Geometry::Interface::Description {
public:
    static VertexDetectorShield& Instance() noexcept;

private:
    VertexDetectorShield() noexcept = default;
    ~VertexDetectorShield() noexcept = default;
    VertexDetectorShield(const VertexDetectorShield&) = delete;
    VertexDetectorShield& operator=(const VertexDetectorShield&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "VertexDetectorShield"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetInnerRadius()  const { return fInnerRadius; }
    [[nodiscard]] const auto& GetInnerLength()  const { return fInnerLength; }
    [[nodiscard]] const auto& GetWindowRadius() const { return fWindowRadius; }
    [[nodiscard]] const auto& GetThickness()    const { return fThickness; }
    [[nodiscard]] const auto& GetCenterX()      const { return fCenterX; }
    [[nodiscard]] const auto& GetUpZPosition()  const { return fUpZPosition; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetCenterX(double val) { fCenterX = val; }
    void SetUpZPosition(double val) { fUpZPosition = val; }

private:
    double fInnerRadius = 25_cm;
    double fInnerLength = 60_cm;
    double fWindowRadius = 16_cm;
    double fThickness = 5_cm;
    double fCenterX = 200_cm;
    double fUpZPosition = 190_cm;
};
