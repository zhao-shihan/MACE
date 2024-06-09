namespace MACE::Detector::Field {

template<typename ADerived>
constexpr ElectromagneticFieldBase<ADerived>::ElectromagneticFieldBase() {
    static_assert(std::derived_from<ADerived, ElectromagneticFieldBase<ADerived>>);
    static_assert(ElectromagneticField<ADerived>);
}

} // namespace MACE::Detector::Field
