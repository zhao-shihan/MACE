#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::Target final :
    public MACE::Geometry::Interface::Description {
public:
    static Target& Instance() noexcept;

private:
    Target() noexcept = default;
    ~Target() noexcept = default;
    Target(const Target&) = delete;
    Target& operator=(const Target&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "Target"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return "Muonium target."; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return "Silica aerogel."; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return "A box with certain width(along XY) and thickness(along Z)."; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return "AcceleratorField"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "Downstream surface at z=0. (Be aware of AcceleratorField's position)"; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetWidth() const { return fWidth; }
    [[nodiscard]] const auto& GetThickness() const { return fThickness; }
    [[nodiscard]] const auto& GetDownZPosition() const { return fDownZPosition; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetDownZPosition(double val) { fDownZPosition = val; }

private:
    double fWidth = 50_mm;
    double fThickness = 10_mm;
    double fDownZPosition = -130_mm;
};
