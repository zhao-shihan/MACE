namespace MACE::Detector::Field {

template<class ADerived, std::floating_point AFloat>
constexpr ElectricFieldBase<ADerived, AFloat>::ElectricFieldBase() :
    ElectromagneticFieldBase<ADerived, AFloat>() {
    static_assert(std::derived_from<ADerived, ElectricFieldBase<ADerived, AFloat>>);
    static_assert(not std::derived_from<ADerived, MagneticFieldBase<ADerived, AFloat>>);
    static_assert(ElectricField<ADerived, AFloat>);
}

} // namespace MACE::Detector::Field
