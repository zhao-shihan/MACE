namespace MACE::Detector::Description {

auto Target::VolumeContain(const Concept::InputVector3D auto& x) const -> bool {
    switch (fShapeType) {
    case TargetShapeType::Cuboid:
        return fCuboid.VolumeContain(x);
    case TargetShapeType::MultiLayer:
        return fMultiLayer.VolumeContain(x);
    }
    std23::unreachable();
}

auto Target::Contain(const Concept::InputVector3D auto& x, bool insideVolume) const -> bool {
    switch (fShapeType) {
    case TargetShapeType::Cuboid:
        return fCuboid.Contain(x, insideVolume);
    case TargetShapeType::MultiLayer:
        return fMultiLayer.Contain(x, insideVolume);
    }
    std23::unreachable();
}

auto Target::DetectableAt(const Concept::InputVector3D auto& x) const -> bool {
    switch (fShapeType) {
    case TargetShapeType::Cuboid:
        return fCuboid.DetectableAt(x);
    case TargetShapeType::MultiLayer:
        return fMultiLayer.DetectableAt(x);
    }
    std23::unreachable();
}

template<typename ADerivedShape>
Target::ShapeBase<ADerivedShape>::ShapeBase() {
    static_assert(
        requires(const ADerivedShape shape, double x[3], bool inside) {
            requires std::is_base_of_v<ShapeBase<ADerivedShape>, ADerivedShape>;
            requires std::is_final_v<ADerivedShape>;
            { shape.VolumeContain(x) } -> std::same_as<bool>;
            { shape.Contain(x, inside) } -> std::same_as<bool>;
            { shape.DetectableAt(x) } -> std::same_as<bool>;
        });
}

template<typename ADerivedShape>
template<typename ADerivedDetail>
Target::ShapeBase<ADerivedShape>::DetailBase<ADerivedDetail>::DetailBase() {
    static_assert(
        requires(const ADerivedDetail detail, double x[3]) {
            requires std::is_base_of_v<DetailBase<ADerivedDetail>, ADerivedDetail>;
            requires std::is_final_v<ADerivedDetail>;
            { detail.DetailContain(x) } -> std::same_as<bool>;
            { detail.DetailDetectable(x) } -> std::same_as<bool>;
        });
}

auto Target::CuboidTarget::VolumeContain(const Concept::InputVector3D auto& x) const -> bool {
    return -fThickness <= x[2] and x[2] <= 0 and
           std23::abs(x[0]) <= fWidth / 2 and
           std23::abs(x[1]) <= fWidth / 2;
}

auto Target::CuboidTarget::Contain(const Concept::InputVector3D auto& x, bool insideVolume) const -> bool {
    switch (fDetailType) {
    case ShapeDetailType::Flat:
        return insideVolume;
    case ShapeDetailType::Perforated:
        return insideVolume and
               fPerforated.DetailContain(x);
    }
    std23::unreachable();
}

auto Target::CuboidTarget::DetectableAt(const Concept::InputVector3D auto& x) const -> bool {
    const auto notShadowed{x[2] > 0 or
                           std23::abs(x[0]) > fWidth / 2 or
                           std23::abs(x[1]) > fWidth / 2};
    switch (fDetailType) {
    case ShapeDetailType::Flat:
        return notShadowed;
    case ShapeDetailType::Perforated:
        return notShadowed or
               fPerforated.DetailDetectable(x);
    }
    std23::unreachable();
}

auto Target::CuboidTarget::PerforatedCuboid::DetailContain(const Concept::InputVector3D auto& x) const -> bool {
    if (x[2] < -fDepth or std23::abs(x[0]) > fHalfExtent or std23::abs(x[1]) > fHalfExtent) {
        return true;
    }
    using std::numbers::sqrt3;
    const auto p{Pitch()};

    const auto u0{p * Math::LLRound((x[0] - (1 / sqrt3) * x[1]) / p)};
    const auto v0{p * Math::LLRound((2 / sqrt3) * x[1] / p)};
    const auto x0{u0 + v0 / 2};
    const auto y0{(sqrt3 / 2) * v0};

    const auto deltaX{x[0] - x0};
    const auto deltaY{x[1] - y0};
    const auto deltaXY2MinusR2{Math::Pow<2>(deltaX) + (deltaY + fRadius) * (deltaY - fRadius)};

    if (deltaXY2MinusR2 <= 0) { return false; }
    const auto deltaXY2MinusR2PlusP2{deltaXY2MinusR2 + Math::Pow<2>(p)};
    const auto pDeltaX{p * deltaX};
    return deltaXY2MinusR2PlusP2 > std23::abs(2 * pDeltaX) and
           deltaXY2MinusR2PlusP2 > std23::abs(pDeltaX + sqrt3 * p * deltaY);
}

auto Target::MultiLayerTarget::VolumeContain(const Concept::InputVector3D auto& x) const -> bool {
    const auto x0{Math::IsEven(fCount) ? fSpacing / 2 : -fThickness / 2};
    const auto r{fSpacing + fThickness};
    const auto u{(x[0] + x0) / r};
    return u - Math::LLRound(u - 0.5) >= fSpacing / r and
           std23::abs(x[0]) <= fCount * r and
           std23::abs(x[1]) <= fHeight / 2 and
           std23::abs(x[2]) <= fWidth / 2;
}

auto Target::MultiLayerTarget::Contain(const Concept::InputVector3D auto& x, bool insideVolume) const -> bool {
    switch (fDetailType) {
    case ShapeDetailType::Flat:
        return insideVolume;
    case ShapeDetailType::Perforated:
        return insideVolume and
               fPerforated.DetailContain(x);
    }
    std23::unreachable();
}

auto Target::MultiLayerTarget::DetectableAt(const Concept::InputVector3D auto& x) const -> bool {
    const auto x0{Math::IsEven(fCount) ? fSpacing / 2 : -fThickness / 2};
    const auto r{fSpacing + fThickness};
    const auto u{(x[0] + x0) / r};
    const auto notShadowed{u - Math::LLRound(u - 0.5) < fSpacing / r or
                           std23::abs(x[0]) > fCount * r or
                           std23::abs(x[1]) > fHeight / 2 or
                           x[2] > fWidth / 2};
    switch (fDetailType) {
    case ShapeDetailType::Flat:
        return notShadowed;
    case ShapeDetailType::Perforated:
        return notShadowed or
               fPerforated.DetailDetectable(x);
    }
    std23::unreachable();
}

auto Target::MultiLayerTarget::PerforatedMultiLayer::DetailContain(const Concept::InputVector3D auto& x) const -> bool {
    if (std23::abs(x[2]) > fHalfExtentZ or std23::abs(x[1]) > fHalfExtentY) {
        return true;
    }
    using std::numbers::sqrt3;
    const auto p{Pitch()};

    const auto u0{p * Math::LLRound((x[2] - (1 / sqrt3) * x[1]) / p)};
    const auto v0{p * Math::LLRound((2 / sqrt3) * x[1] / p)};
    const auto z0{u0 + v0 / 2};
    const auto y0{(sqrt3 / 2) * v0};

    const auto deltaZ{x[2] - z0};
    const auto deltaY{x[1] - y0};
    const auto deltaZY2MinusR2{Math::Pow<2>(deltaZ) + (deltaY + fRadius) * (deltaY - fRadius)};

    if (deltaZY2MinusR2 <= 0) { return false; }
    const auto deltaZY2MinusR2PlusP2{deltaZY2MinusR2 + Math::Pow<2>(p)};
    const auto pDeltaZ{p * deltaZ};
    return deltaZY2MinusR2PlusP2 > std23::abs(2 * pDeltaZ) and
           deltaZY2MinusR2PlusP2 > std23::abs(pDeltaZ + sqrt3 * p * deltaY);
}

} // namespace MACE::Detector::Description
