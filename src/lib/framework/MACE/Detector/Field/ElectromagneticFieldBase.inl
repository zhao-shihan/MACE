namespace MACE::Detector::Field {

template<typename ADerived>
template<Concept::NumericVector3D T>
constexpr auto ElectromagneticFieldBase<ADerived>::BE(T x) const -> F<T> {
    static_assert(std::derived_from<ADerived, ElectromagneticFieldBase<ADerived>>);
    static_assert(ElectromagneticField<ADerived>);
    return {static_cast<const ADerived*>(this)->B(x),
            static_cast<const ADerived*>(this)->E(x)};
}

} // namespace MACE::Detector::Field
