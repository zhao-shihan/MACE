#pragma once

#include "Core/Geometry/Description/AcceleratorField.hxx"

namespace MACE::Core::Geometry::Description {

class Target final : public IDescription {
public:
    static Target& Instance() noexcept;

private:
    Target() = default;
    ~Target() noexcept = default;
    Target(const Target&) = delete;
    Target& operator=(const Target&) = delete;

public:
    std::string GetName() const override { return "Target"; }
    std::string GetOverallDescription() const override { return "Muonium target."; }
    std::string GetMaterialDescription() const override { return "Silica aerogel."; }
    std::string GetShapeDescription() const override { return "A box with certain width(along XY) and thickness(along Z)."; }
    std::string GetMotherDescription() const override { return "AcceleratorField"; }
    std::string GetTranslationDescription() const override { return "Downstream surface at z=0. (Be aware of AcceleratorField's position)"; }
    std::string GetRotationDescription() const override { return "No rotation."; }

    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }
    G4Transform3D GetTransform() const;

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fWidth = 6_cm;
    double fThickness = 1_cm;
};

} // namespace MACE::Core::Geometry::Description
