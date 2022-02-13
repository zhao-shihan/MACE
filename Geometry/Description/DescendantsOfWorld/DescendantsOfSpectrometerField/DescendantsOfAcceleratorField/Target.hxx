#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::Target final :
    public MACE::Geometry::Interface::Description {
public:
    static Target& Instance();

private:
    Target() noexcept {}
    ~Target() noexcept {}
    Target(const Target&) = delete;
    Target& operator=(const Target&) = delete;

public:
    const char* GetName()                   const override { return "Target"; }
    const char* GetOverallDescription()     const override { return "Muonium target."; }
    const char* GetMaterialDescription()    const override { return "Silica aerogel."; }
    const char* GetShapeDescription()       const override { return "A box with certain width(along XY) and thickness(along Z)."; }
    const char* GetMotherDescription()      const override { return "AcceleratorField"; }
    const char* GetTranslationDescription() const override { return "Downstream surface at z=0. (Be aware of AcceleratorField's position)"; }
    const char* GetRotationDescription()    const override { return "No rotation."; }

    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }
    const auto& GetDownZPosition() const { return fDownZPosition; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetDownZPosition(double val) { fDownZPosition = val; }

private:
    double fWidth = 50_mm;
    double fThickness = 10_mm;
    double fDownZPosition = -130_mm;
};
