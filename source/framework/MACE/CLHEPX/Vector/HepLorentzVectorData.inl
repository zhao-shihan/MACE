namespace MACE::CLHEPX::Vector {

namespace internal {

template class ForbiddenLore<&CLHEP::HepLorentzVector::pp>;

constexpr CLHEP::Hep3Vector& ForbiddenGet(CLHEP::HepLorentzVector&);
constexpr const CLHEP::Hep3Vector& ForbiddenGet(const CLHEP::HepLorentzVector&);

} // namespace internal

namespace HepLorentzVectorData {

#ifdef __cpp_lib_is_layout_compatible

namespace internal {

class HepLorentzVectorImitator {
    Hep3VectorData::internal::Hep3VectorImitator pp;
    double ee;
};

} // namespace internal

#endif

constexpr double* operator&(CLHEP::HepLorentzVector& vector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::HepLorentzVector>);
    static_assert(sizeof(CLHEP::HepLorentzVector) == 4 * sizeof(double));
    static_assert(alignof(CLHEP::HepLorentzVector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<internal::HepLorentzVectorImitator>);
    static_assert(sizeof(internal::HepLorentzVectorImitator) == 4 * sizeof(double));
    static_assert(alignof(internal::HepLorentzVectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::HepLorentzVector, internal::HepLorentzVectorImitator>);
#endif
    using Hep3VectorData::operator&;
    return std::launder(&Vector::internal::ForbiddenGet(vector));
}

constexpr const double* operator&(const CLHEP::HepLorentzVector& vector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::HepLorentzVector>);
    static_assert(sizeof(CLHEP::HepLorentzVector) == 4 * sizeof(double));
    static_assert(alignof(CLHEP::HepLorentzVector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<internal::HepLorentzVectorImitator>);
    static_assert(sizeof(internal::HepLorentzVectorImitator) == 4 * sizeof(double));
    static_assert(alignof(internal::HepLorentzVectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::HepLorentzVector, internal::HepLorentzVectorImitator>);
#endif
    using Hep3VectorData::operator&;
    return std::launder(&Vector::internal::ForbiddenGet(vector));
}

} // namespace HepLorentzVectorData

} // namespace MACE::CLHEPX::Vector
