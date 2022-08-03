namespace MACE::Utility::CLHEPHepLorentzVectorData {

#ifdef __cpp_lib_is_layout_compatible

namespace Detail {

class HepLorentzVectorImitator {
    class Hep3VectorImitator {
        double data[3];
    } pp;
    double ee;
};

} // namespace Detail

#endif

inline double* operator&(CLHEP::HepLorentzVector& fourVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::HepLorentzVector>);
    static_assert(sizeof(CLHEP::HepLorentzVector) == 4 * sizeof(double));
    static_assert(alignof(CLHEP::HepLorentzVector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Detail::HepLorentzVectorImitator>);
    static_assert(sizeof(Detail::HepLorentzVectorImitator) == 4 * sizeof(double));
    static_assert(alignof(Detail::HepLorentzVectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::HepLorentzVector, Detail::HepLorentzVectorImitator>);
#endif
    return std::launder(reinterpret_cast<double*>(&fourVector));
}

inline const double* operator&(const CLHEP::HepLorentzVector& fourVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::HepLorentzVector>);
    static_assert(sizeof(CLHEP::HepLorentzVector) == 4 * sizeof(double));
    static_assert(alignof(CLHEP::HepLorentzVector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Detail::HepLorentzVectorImitator>);
    static_assert(sizeof(Detail::HepLorentzVectorImitator) == 4 * sizeof(double));
    static_assert(alignof(Detail::HepLorentzVectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::HepLorentzVector, Detail::HepLorentzVectorImitator>);
#endif
    return std::launder(reinterpret_cast<const double*>(&fourVector));
}

} // namespace MACE::Utility::CLHEPHepLorentzVectorData
