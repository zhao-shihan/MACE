#pragma once

#include <cmath>

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SelectorField final :
    public MACE::Geometry::Interface::Description {
public:
    static SelectorField& Instance() noexcept;

private:
    SelectorField() noexcept = default;
    ~SelectorField() noexcept = default;
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SelectorField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRadius()    const { return fRadius; }
    [[nodiscard]] const auto& GetLength()    const { return fLength; }
    [[nodiscard]] const auto& GetZPosition() const { return fZPosition; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 5_cm;
    double fLength = 30_cm;
    double fZPosition = 20_cm;
};
