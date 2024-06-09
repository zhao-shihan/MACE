namespace MACE::Detector::Field {

template<Concept::MathVector<double, 6> AStorageVector>
template<Concept::NumericVector3D T>
auto TrilerpElectromagneticField<"WithCache", AStorageVector>::B(T x) const -> T {
    const auto xEigen{VectorCast<Eigen::Vector3d>(x)};
    if (xEigen != fCachedX or fCache == std::nullopt) {
        fCachedX = xEigen;
        fCache = (*this)(x[0], x[1], x[2]);
    }
    return {fCache[0], fCache[1], fCache[2]};
}

template<Concept::MathVector<double, 6> AStorageVector>
template<Concept::NumericVector3D T>
auto TrilerpElectromagneticField<"WithCache", AStorageVector>::E(T x) const -> T {
    const auto xEigen{VectorCast<Eigen::Vector3d>(x)};
    if (xEigen != fCachedX or fCache == std::nullopt) {
        fCachedX = xEigen;
        fCache = (*this)(x[0], x[1], x[2]);
    }
    return {fCache[3], fCache[4], fCache[5]};
}

template<Concept::MathVector<double, 6> AStorageVector>
template<Concept::NumericVector3D T>
auto TrilerpElectromagneticField<"WithCache", AStorageVector>::BE(T x) const -> F<T> {
    fCachedX = VectorCast<Eigen::Vector3d>(x);
    fCache = (*this)(x[0], x[1], x[2]);
    return {VectorCast<T>(fCache[0], fCache[1], fCache[2]),
            VectorCast<T>(fCache[3], fCache[4], fCache[5])};
}

template<Concept::MathVector<double, 6> AStorageVector>
template<Concept::NumericVector3D T>
auto TrilerpElectromagneticField<"NoCache", AStorageVector>::B(T x) const -> T {
    const auto v{(*this)(x[0], x[1], x[2])};
    return {VectorCast<T>(v[0], v[1], v[2])};
}

template<Concept::MathVector<double, 6> AStorageVector>
template<Concept::NumericVector3D T>
auto TrilerpElectromagneticField<"NoCache", AStorageVector>::E(T x) const -> T {
    const auto v{(*this)(x[0], x[1], x[2])};
    return {VectorCast<T>(v[3], v[4], v[5])};
}

template<Concept::MathVector<double, 6> AStorageVector>
template<Concept::NumericVector3D T>
auto TrilerpElectromagneticField<"NoCache", AStorageVector>::BE(T x) const -> F<T> {
    const auto v{(*this)(x[0], x[1], x[2])};
    return {VectorCast<T>(v[0], v[1], v[2]),
            VectorCast<T>(v[3], v[4], v[5])};
}

} // namespace MACE::Detector::Field
