namespace MACE::Detector::Field {

template<typename ADerived>
template<Concept::NumericVector3D T>
constexpr auto ElectromagneticFieldBase<ADerived>::BEFieldAt(T x) const -> F<T> {
    static_assert(std::derived_from<ADerived, ElectromagneticFieldBase<ADerived>>);
    static_assert(ElectromagneticField<ADerived>);
    return {static_cast<const ADerived*>(this)->BFieldAt(x),
            static_cast<const ADerived*>(this)->EFieldAt(x)};
}

} // namespace MACE::Detector::Field
