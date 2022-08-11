namespace MACE::Utility::CLHEPVectorX::Hep2VectorData {

#ifdef __cpp_lib_is_layout_compatible

namespace Internal {

class Hep2VectorImitator {
    double dx;
    double dy;
};

} // namespace Internal

#endif

inline double* operator&(CLHEP::Hep2Vector& twoVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::Hep2Vector>);
    static_assert(sizeof(CLHEP::Hep2Vector) == 2 * sizeof(double));
    static_assert(alignof(CLHEP::Hep2Vector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Internal::Hep2VectorImitator>);
    static_assert(sizeof(Internal::Hep2VectorImitator) == 2 * sizeof(double));
    static_assert(alignof(Internal::Hep2VectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::Hep2Vector, Internal::Hep2VectorImitator>);
#endif
    return std::launder(reinterpret_cast<double*>(std::addressof(twoVector)));
}

inline const double* operator&(const CLHEP::Hep2Vector& twoVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::Hep2Vector>);
    static_assert(sizeof(CLHEP::Hep2Vector) == 2 * sizeof(double));
    static_assert(alignof(CLHEP::Hep2Vector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Internal::Hep2VectorImitator>);
    static_assert(sizeof(Internal::Hep2VectorImitator) == 2 * sizeof(double));
    static_assert(alignof(Internal::Hep2VectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::Hep2Vector, Internal::Hep2VectorImitator>);
#endif
    return std::launder(reinterpret_cast<const double*>(std::addressof(twoVector)));
}

} // namespace MACE::Utility::CLHEPHep2VectorData
