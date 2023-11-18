namespace MACE::Detector::Field {

template<typename ADerived, std::floating_point AFloat>
constexpr MagneticFieldBase<ADerived, AFloat>::MagneticFieldBase() :
    ElectromagneticFieldBase<ADerived, AFloat>() {
    static_assert(std::derived_from<ADerived, MagneticFieldBase<ADerived, AFloat>>);
    static_assert(not std::derived_from<ADerived, ElectricFieldBase<ADerived, AFloat>>);
    static_assert(MagneticField<ADerived, AFloat>);
}

} // namespace MACE::Detector::Field
