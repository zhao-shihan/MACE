#pragma once

#include "MACE/Compatibility/std2b/unreachable.hxx"
#include "MACE/Concept/MathVector.hxx"
#include "MACE/Core/Geometry/IDescription.hxx"
#include "MACE/Env/Memory/MuteSingleton.hxx"
#include "MACE/Math/Hypot.hxx"
#include "MACE/Math/IntegerPower.hxx"

#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Vector/ThreeVector.h"

#include <cmath>
#include <concepts>
#include <numbers>

namespace MACE::Core::Geometry::Description {

class Target final : public ISingletonDescription<Target> {
    friend Env::Memory::SingletonFactory;

public:
    enum class TargetShapeType {
        Cuboid
    };

    template<class ADerivedShape>
    class ShapeBase : public Env::Memory::MuteSingleton<ADerivedShape> {
    protected:
        ShapeBase();
        ~ShapeBase() = default;

    protected:
        template<class ADerivedDetail>
        class DetailBase : public Env::Memory::MuteSingleton<ADerivedDetail> {
        protected:
            DetailBase();
            ~DetailBase() = default;
        };
    };

    class CuboidTarget final : public ShapeBase<CuboidTarget> {
    public:
        enum class ShapeDetailType {
            Flat,
            Hole
        };

    public:
        CuboidTarget();

        const auto& Width() const { return fWidth; }
        const auto& Thickness() const { return fThickness; }

        void Width(double val) { fWidth = val; }
        void Thickness(double val) { fThickness = val; }

        /// @attention Should only be used for geometry construction.
        HepGeom::Transform3D CalcTransform() const;

        const auto& DetailType() const { return fDetailType; }
        void DetailType(ShapeDetailType val) { fDetailType = val; }
        const auto& Hole() const { return fHole; }
        auto& Hole() { return fHole; }

        bool VolumeContain(const Concept::MathVector3D auto& x) const noexcept;
        bool Contain(const Concept::MathVector3D auto& x, bool insideVolume) const noexcept;
        bool TestDetectable(const Concept::MathVector3D auto& x) const noexcept;

    private:
        class HoledCuboid final : public DetailBase<HoledCuboid> {
        public:
            HoledCuboid();

            void Extent(double ex) { fHalfExtent = ex / 2; }
            void Spacing(double spacing);
            void Diameter(double diameter);
            void Depth(double d) { fDepth = d; }

            auto HalfExtent() const { return fHalfExtent; }
            auto Extent() const { return 2 * fHalfExtent; }
            auto Spacing() const { return fSpacing; }
            auto Radius() const { return fRadius; }
            auto Diameter() const { return 2 * fRadius; }
            auto Depth() const { return fDepth; }
            auto Pitch() const { return fPitch; }

            bool DetailContain(const Concept::MathVector3D auto& x) const noexcept;
            bool DetailDetectable(const Concept::MathVector3D auto&) const noexcept { return false; }

        private:
            double fHalfExtent;
            double fSpacing;
            double fRadius;
            double fDepth;
            double fPitch;
        };

    private:
        double fWidth;
        double fThickness;

        ShapeDetailType fDetailType;
        HoledCuboid fHole;
    };

private:
    Target();
    ~Target() = default;

public:
    const auto& ShapeType() const { return fShapeType; }
    void ShapeType(TargetShapeType val) { fShapeType = val; }
    const auto& Cuboid() const { return fCuboid; }
    auto& Cuboid() { return fCuboid; }

    /// @brief Return true if inside the target volume (include boundary (closed region), don't consider fine structure).
    bool VolumeContain(const Concept::MathVector3D auto& x) const noexcept;
    /// @brief Return true if inside the exact target geometry (considering fine structure).
    bool Contain(const Concept::MathVector3D auto& x, bool insideVolume) const noexcept;
    bool Contain(const Concept::MathVector3D auto& x) const noexcept { return Contain(x, VolumeContain(x)); }
    /// @brief Return true if the decay position x is detectable (i.e. is not shadowed by target).
    bool TestDetectable(const Concept::MathVector3D auto& x) const noexcept;

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    TargetShapeType fShapeType;
    CuboidTarget fCuboid;
};

} // namespace MACE::Core::Geometry::Description

#include "MACE/Core/Geometry/Description/Target.inl"
