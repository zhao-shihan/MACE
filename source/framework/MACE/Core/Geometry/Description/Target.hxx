#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"
#include "MACE/Utility/Math/Hypot.hxx"
#include "MACE/Utility/Math/IntegerPower.hxx"
#include "MACE/Utility/Math/RealVectorSpace.hxx"

#include "CLHEP/Geometry/Transform3D.h"

#include <cmath>

namespace MACE::Core::Geometry::Description {

using Utility::Math::Concept::R3VectorSpace;

class Target final : public ISingletonDescription<Target> {
    friend Environment::Memory::SingletonFactory;

private:
    Target();
    ~Target() = default;

public:
    const auto& GetWidth() const { return fWidth; }
    const auto& GetThickness() const { return fThickness; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

    // Next 1 method should only be used for geometry construction.

    HepGeom::Transform3D CalcTransform() const;

private:
    class HoleAblation final {
    public:
        HoleAblation(double extent, double spacing, double diameter, double depth);

        void SetExtent(double ex) { fHalfExtent = ex / 2; }
        void SetSpacing(double spacing);
        void SetDiameter(double diameter);
        void SetDepth(double d) { fDepth = d; }

        auto GetHalfExtent() const { return fHalfExtent; }
        auto GetExtent() const { return 2 * fHalfExtent; }
        auto GetSpacing() const { return fSpacing; }
        auto GetRadius() const { return fRadius; }
        auto GetDiameter() const { return 2 * fRadius; }
        auto GetDepth() const { return fDepth; }
        auto GetPitch() const { return fPitch; }

        bool TestExtraStructure(const R3VectorSpace auto& x) const noexcept;
        bool TestExtraDetectable(const R3VectorSpace auto&) const noexcept { return false; }

    private:
        double fHalfExtent;
        double fSpacing;
        double fRadius;
        double fDepth;
        double fPitch;
    };

public:
    auto& GetExtraStructure() { return fHole; }
    const auto& GetExtraStructure() const { return fHole; }

    /// @brief Return true if inside the target volume (include boundary (closed region), don't consider fine structure).
    bool VolumeContains(const R3VectorSpace auto& x) const noexcept;
    /// @brief Return true if inside the exact target geometry (considering fine structure).
    bool Contains(const R3VectorSpace auto& x, bool insideVolume) const noexcept { return insideVolume and GetExtraStructure().TestExtraStructure(x); }
    bool Contains(const R3VectorSpace auto& x) const noexcept { return Contains(x, VolumeContains(x)); }
    /// @brief Return true if the decay position x is detectable (i.e. is not shadowed by target).
    bool TestDetectable(const R3VectorSpace auto& x) const noexcept;

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fWidth;
    double fThickness;

    HoleAblation fHole;
};

} // namespace MACE::Core::Geometry::Description

#include "MACE/Core/Geometry/Description/Target.inl"
