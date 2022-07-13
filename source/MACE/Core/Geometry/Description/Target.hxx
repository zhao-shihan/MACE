#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

#include "TFormula.h"

namespace MACE::Core::Geometry::Description {

class Target final : public IDescriptionSingleton<Target> {
    friend Singleton<Target>;

private:
    Target();
    ~Target() noexcept = default;
    Target(const Target&) = delete;
    Target& operator=(const Target&) = delete;

public:
    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }
    /// Return true if inside the target volume (include boundary (closed region), don't consider fine structure).
    bool VolumeContains(const Double_t* pos) const noexcept;
    bool VolumeContains(const CLHEP::Hep3Vector& pos) const noexcept;
    /// Return true if inside the exact target geometry (include boundary (closed region), considering fine structure).
    bool Contains(const Double_t* pos) const noexcept { return VolumeContains(pos) and fFineStructure.EvalPar(pos); }
    bool Contains(const CLHEP::Hep3Vector& pos) const noexcept;

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetFineStructure(const char* booleanExpression) { fFineStructure = ConstructFormula(booleanExpression); }

    // Next 1 method should only use for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

    static TFormula ConstructFormula(const char* booleanExpression) { return TFormula("TargetFineStructure", booleanExpression, false); }

private:
    double fWidth;
    double fThickness;
    TFormula fFineStructure;
};

} // namespace MACE::Core::Geometry::Description
