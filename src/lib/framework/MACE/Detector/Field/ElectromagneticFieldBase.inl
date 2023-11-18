namespace MACE::Detector::Field {

template<typename ADerived, std::floating_point AFloat>
constexpr ElectromagneticFieldBase<ADerived, AFloat>::ElectromagneticFieldBase() {
    static_assert(std::derived_from<ADerived, ElectromagneticFieldBase<ADerived, AFloat>>);
    static_assert(ElectromagneticField<ADerived, AFloat>);
}

template<typename ADerived, std::floating_point AFloat>
template<Concept::NumericVector3<AFloat> T>
constexpr stdx::array2<T> ElectromagneticFieldBase<ADerived, AFloat>::BEFieldAt(const T& x) const {
    return {static_cast<const ADerived*>(this)->BFieldAt(x),
            static_cast<const ADerived*>(this)->EFieldAt(x)};
}

} // namespace MACE::Detector::Field
