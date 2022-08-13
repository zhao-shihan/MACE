namespace MACE::Utility::CLHEPVectorX::HepLorentzVectorData {

#ifdef __cpp_lib_is_layout_compatible

namespace Internal {

class HepLorentzVectorImitator {
    class Hep3VectorImitator {
        double data[3];
    } pp;
    double ee;
};

} // namespace Internal

#endif

inline double* operator&(CLHEP::HepLorentzVector& fourVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::HepLorentzVector>);
    static_assert(sizeof(CLHEP::HepLorentzVector) == 4 * sizeof(double));
    static_assert(alignof(CLHEP::HepLorentzVector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Internal::HepLorentzVectorImitator>);
    static_assert(sizeof(Internal::HepLorentzVectorImitator) == 4 * sizeof(double));
    static_assert(alignof(Internal::HepLorentzVectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::HepLorentzVector, Internal::HepLorentzVectorImitator>);
#endif
    return std::launder(reinterpret_cast<double*>(std::addressof(fourVector)));
}

inline const double* operator&(const CLHEP::HepLorentzVector& fourVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::HepLorentzVector>);
    static_assert(sizeof(CLHEP::HepLorentzVector) == 4 * sizeof(double));
    static_assert(alignof(CLHEP::HepLorentzVector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Internal::HepLorentzVectorImitator>);
    static_assert(sizeof(Internal::HepLorentzVectorImitator) == 4 * sizeof(double));
    static_assert(alignof(Internal::HepLorentzVectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::HepLorentzVector, Internal::HepLorentzVectorImitator>);
#endif
    return std::launder(reinterpret_cast<const double*>(std::addressof(fourVector)));
}

} // namespace MACE::Utility::CLHEPVectorX::HepLorentzVectorData
