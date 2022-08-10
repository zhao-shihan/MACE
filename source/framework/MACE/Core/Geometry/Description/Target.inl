namespace MACE::Core::Geometry::Description {

bool Target::VolumeContains(const MathVector3D auto& x) const noexcept {
    switch (fShape) {
    case ShapeType::Cuboid:
        return fCuboid.VolumeContains(x);
    }
    Cxx2b::Unreachable();
}

bool Target::Contains(const MathVector3D auto& x, bool insideVolume) const noexcept {
    switch (fShape) {
    case ShapeType::Cuboid:
        return fCuboid.Contains(x, insideVolume);
    }
    Cxx2b::Unreachable();
}

bool Target::TestDetectable(const MathVector3D auto& x) const noexcept {
    switch (fShape) {
    case ShapeType::Cuboid:
        return fCuboid.TestDetectable(x);
    }
    Cxx2b::Unreachable();
}

template<class ADerivedShape>
Target::ShapeBase<ADerivedShape>::ShapeBase() {
    static_assert( // clang-format off
        requires(const ADerivedShape& shape, CLHEP::Hep3Vector&& x, bool&& inside) { // clang-format on
            requires std::is_base_of_v<ShapeBase<ADerivedShape>, ADerivedShape>;
            requires std::is_final_v<ADerivedShape>;
            { shape.CalcTransform() } -> std::same_as<HepGeom::Transform3D>;
            { shape.VolumeContains(x) } -> std::same_as<bool>;
            { shape.Contains(x, inside) } -> std::same_as<bool>;
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
            { detail.TestDetailedShape(x) } -> std::same_as<bool>;
            { detail.TestDetailedDetectable(x) } -> std::same_as<bool>;
        });
}

bool Target::Cuboid::VolumeContains(const MathVector3D auto& x) const noexcept {
    return -fThickness <= x[2] and x[2] <= 0 and
           std::abs(x[0]) <= fWidth / 2 and
           std::abs(x[1]) <= fWidth / 2;
}

bool Target::Cuboid::Contains(const MathVector3D auto& x, bool insideVolume) const noexcept {
    switch (fDetail) {
    case DetailType::Flat:
        return insideVolume;
    case DetailType::Hole:
        return insideVolume and
               fHole.TestDetailedShape(x);
    }
    Cxx2b::Unreachable();
}

bool Target::Cuboid::TestDetectable(const MathVector3D auto& x) const noexcept {
    const auto notShadowed = x[2] > 0 or
                             std::abs(x[0]) > fWidth / 2 or
                             std::abs(x[1]) > fWidth / 2;
    switch (fDetail) {
    case DetailType::Flat:
        return notShadowed;
    case DetailType::Hole:
        return notShadowed or
               fHole.TestDetailedDetectable(x);
    }
    Cxx2b::Unreachable();
}

bool Target::Cuboid::Hole::TestDetailedShape(const MathVector3D auto& x) const noexcept {
    if (x[2] < -fDepth or std::abs(x[0]) > fHalfExtent or std::abs(x[1]) > fHalfExtent) {
        return true;
    } else {
        using Utility::Math::Hypot2;
        using Utility::Math::Pow2;
        constexpr auto sqrt3 = 1.732050807568877294;
        const auto u = std::round((x[0] - (1 / sqrt3) * x[1]) / fPitch) * fPitch;
        const auto v = std::round((2 / sqrt3) * x[1] / fPitch) * fPitch;
        return Hypot2(x[0] - (u + v / 2), x[1] - (sqrt3 / 2) * v) > Pow2(fRadius);
    }
}

} // namespace MACE::Core::Geometry::Description
