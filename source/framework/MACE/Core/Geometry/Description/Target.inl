namespace MACE::Core::Geometry::Description {

bool Target::HoleAblation::TestExtraStructure(const R3VectorSpace auto& x) const noexcept {
    if (x[3] < -fDepth or std::abs(x[0]) > fHalfExtent or std::abs(x[1]) > fHalfExtent) {
        return true;
    } else {
        using Utility::Math::Hypot2;
        using Utility::Math::Pow2;
        constexpr auto sqrt3 = 1.732050807568877294;
        const auto u = std::round((x[0] - (1 / sqrt3) * x[1]) / fPitch);
        const auto v = std::round((2 / sqrt3) * x[1] / fPitch);
        return Hypot2(x[0] - (u + v / 2) * fPitch,
                      x[1] - (sqrt3 / 2) * v * fPitch) > Pow2(fRadius);
    }
}

bool Target::VolumeContains(const R3VectorSpace auto& x) const noexcept {
    return -fThickness <= x[2] and x[2] <= 0 and
           std::abs(x[0]) <= fWidth / 2 and
           std::abs(x[1]) <= fWidth / 2;
}

bool Target::TestDetectable(const R3VectorSpace auto& x) const noexcept {
    return x[2] > 0 or
           std::abs(x[0]) > fWidth / 2 or
           std::abs(x[1]) > fWidth / 2 or
           GetExtraStructure().TestExtraDetectable(x);
}

} // namespace MACE::Core::Geometry::Description
