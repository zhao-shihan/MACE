#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::Collimator final :
    public MACE::Geometry::Interface::Description {
public:
    static Collimator& Instance() noexcept;

private:
    Collimator() noexcept = default;
    ~Collimator() noexcept = default;
    Collimator(const Collimator&) = delete;
    Collimator& operator=(const Collimator&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "Collimator"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return ""; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return ""; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return ""; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return ""; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetInnerRadius() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetOuterRadius() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetLength()      const { return fLength; }
    [[nodiscard]] const auto& GetThickness()   const { return fThickness; }
    [[nodiscard]] const auto& GetZPosition()   const { return fZPosition; }
    [[nodiscard]] const auto& GetCount()       const { return fCount; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetZPosition(double val) { fZPosition = val; }
    void SetCount(int val) { fCount = val; }

private:
    double fInnerRadius = 5_mm;
    double fOuterRadius = 75_mm;
    double fLength = 30_cm;
    double fZPosition = -20_cm;
    double fThickness = 1_mm;
    int fCount = 5;
};
