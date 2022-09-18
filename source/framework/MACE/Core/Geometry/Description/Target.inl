namespace MACE::Core::Geometry::Description {

namespace std2b = Compatibility::std2b;

bool Target::VolumeContain(const MathVector3D auto& x) const noexcept {
    switch (fShapeType) {
    case TargetShapeType::Cuboid:
        return fCuboid.VolumeContain(x);
    }
    std2b::unreachable();
}

bool Target::Contain(const MathVector3D auto& x, bool insideVolume) const noexcept {
    switch (fShapeType) {
    case TargetShapeType::Cuboid:
        return fCuboid.Contain(x, insideVolume);
    }
    std2b::unreachable();
}

bool Target::TestDetectable(const MathVector3D auto& x) const noexcept {
    switch (fShapeType) {
    case TargetShapeType::Cuboid:
        return fCuboid.TestDetectable(x);
    }
    std2b::unreachable();
}

template<class ADerivedShape>
Target::ShapeBase<ADerivedShape>::ShapeBase() {
    static_assert( // clang-format off
        requires(const ADerivedShape& shape, CLHEP::Hep3Vector&& x, bool&& inside) { // clang-format on
            requires std::is_base_of_v<ShapeBase<ADerivedShape>, ADerivedShape>;
            requires std::is_final_v<ADerivedShape>;
            { shape.CalcTransform() } -> std::same_as<HepGeom::Transform3D>;
            { shape.VolumeContain(x) } -> std::same_as<bool>;
            { shape.Contain(x, inside) } -> std::same_as<bool>;
            { shape.TestDetectable(x) } -> std::same_as<bool>;
        });
}

template<class ADerivedShape>
template<class ADerivedDetail>
Target::ShapeBase<ADerivedShape>::DetailBase<ADerivedDetail>::DetailBase() {
    static_assert( // clang-format off
        requires(const ADerivedDetail& detail, CLHEP::Hep3Vector&& x) { // clang-format on
            requires std::is_base_of_v<DetailBase<ADerivedDetail>, ADerivedDetail>;
            requires std::is_final_v<ADerivedDetail>;
            { detail.DetailContain(x) } -> std::same_as<bool>;
            { detail.DetailDetectable(x) } -> std::same_as<bool>;
        });
}

bool Target::CuboidTarget::VolumeContain(const MathVector3D auto& x) const noexcept {
    return -fThickness <= x[2] and x[2] <= 0 and
           std::abs(x[0]) <= fWidth / 2 and
           std::abs(x[1]) <= fWidth / 2;
}

bool Target::CuboidTarget::Contain(const MathVector3D auto& x, bool insideVolume) const noexcept {
    switch (fDetailType) {
    case ShapeDetailType::Flat:
        return insideVolume;
    case ShapeDetailType::Hole:
        return insideVolume and
               fHole.DetailContain(x);
    }
    std2b::unreachable();
}

bool Target::CuboidTarget::TestDetectable(const MathVector3D auto& x) const noexcept {
    const auto notShadowed = x[2] > 0 or
                             std::abs(x[0]) > fWidth / 2 or
                             std::abs(x[1]) > fWidth / 2;
    switch (fDetailType) {
    case ShapeDetailType::Flat:
        return notShadowed;
    case ShapeDetailType::Hole:
        return notShadowed or
               fHole.DetailDetectable(x);
    }
    std2b::unreachable();
}

bool Target::CuboidTarget::HoledCuboid::DetailContain(const MathVector3D auto& x) const noexcept {
    if (x[2] < -fDepth or std::abs(x[0]) > fHalfExtent or std::abs(x[1]) > fHalfExtent) {
        return true;
    } else {
        using std::numbers::sqrt3;
        using Utility::Math::Hypot2;
        using Utility::Math::Pow2;
        const auto u = std::round((x[0] - (1 / sqrt3) * x[1]) / fPitch) * fPitch;
        const auto v = std::round((2 / sqrt3) * x[1] / fPitch) * fPitch;
        return Hypot2(x[0] - (u + v / 2), x[1] - (sqrt3 / 2) * v) > Pow2(fRadius);
    }
}

} // namespace MACE::Core::Geometry::Description
