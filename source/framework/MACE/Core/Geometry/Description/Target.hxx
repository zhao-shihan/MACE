#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"
#include "MACE/Cxx2b/Unreachable.hxx"
#include "MACE/Environment/Memory/MuteSingleton.hxx"
#include "MACE/Utility/Concept/MathVector.hxx"
#include "MACE/Utility/Math/Hypot.hxx"
#include "MACE/Utility/Math/IntegerPower.hxx"

#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Vector/ThreeVector.h"

#include <cmath>
#include <concepts>

namespace MACE::Core::Geometry::Description {

using Utility::Concept::MathVector3D;

class Target final : public ISingletonDescription<Target> {
    friend Environment::Memory::SingletonFactory;

public:
    enum class ShapeType {
        Cuboid
    };

private:
    Target();
    ~Target() = default;

public:
    const auto& GetShapeType() const { return fShape; }
    void SetShapeType(ShapeType val) { fShape = val; }
    const auto& GetCuboid() const { return fCuboid; }
    auto& GetCuboid() { return fCuboid; }

    /// @brief Return true if inside the target volume (include boundary (closed region), don't consider fine structure).
    bool VolumeContains(const MathVector3D auto& x) const noexcept;
    /// @brief Return true if inside the exact target geometry (considering fine structure).
    bool Contains(const MathVector3D auto& x, bool insideVolume) const noexcept;
    bool Contains(const MathVector3D auto& x) const noexcept { return Contains(x, VolumeContains(x)); }
    /// @brief Return true if the decay position x is detectable (i.e. is not shadowed by target).
    bool TestDetectable(const MathVector3D auto& x) const noexcept;

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    template<class ADerivedShape>
    class ShapeBase : public Environment::Memory::MuteSingleton<ADerivedShape> {
    protected:
        ShapeBase();
        ~ShapeBase() = default;

    protected:
        template<class ADerivedDetail>
        class DetailBase : public Environment::Memory::MuteSingleton<ADerivedDetail> {
        protected:
            DetailBase();
            ~DetailBase() = default;
        };
    };

    class Cuboid final : public ShapeBase<Cuboid> {
    public:
        enum class DetailType {
            Flat,
            Hole
        };

    public:
        Cuboid();

        const auto& GetWidth() const { return fWidth; }
        const auto& GetThickness() const { return fThickness; }

        void SetWidth(double val) { fWidth = val; }
        void SetThickness(double val) { fThickness = val; }

        /// @attention Should only be used for geometry construction.
        HepGeom::Transform3D CalcTransform() const;

        const auto& GetDetailType() const { return fDetail; }
        void SetDetailType(DetailType val) { fDetail = val; }
        const auto& GetHole() const { return fHole; }
        auto& GetHole() { return fHole; }

        bool VolumeContains(const MathVector3D auto& x) const noexcept;
        bool Contains(const MathVector3D auto& x, bool insideVolume) const noexcept;
        bool TestDetectable(const MathVector3D auto& x) const noexcept;

    private:
        class Hole final : public DetailBase<Hole> {
        public:
            Hole();

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

            bool TestDetailedShape(const MathVector3D auto& x) const noexcept;
            bool TestDetailedDetectable(const MathVector3D auto&) const noexcept { return false; }

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

        DetailType fDetail;
        Hole fHole;
    };

private:
    ShapeType fShape;
    Cuboid fCuboid;
};

} // namespace MACE::Core::Geometry::Description

#include "MACE/Core/Geometry/Description/Target.inl"
