#pragma once

#include "Core/Geometry/Description/AcceleratorField.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class Target final : public IDescription {
public:
    static Target& Instance() noexcept;

private:
    Target();
    ~Target() noexcept = default;
    Target(const Target&) = delete;
    Target& operator=(const Target&) = delete;

public:
    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }
    G4Transform3D GetTransform() const;

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    void ReadImpl(const YAML::Node& node) override;
    void WriteImpl(YAML::Node& node) const override;

private:
    double fWidth;
    double fThickness;
};

} // namespace MACE::Core::Geometry::Description
