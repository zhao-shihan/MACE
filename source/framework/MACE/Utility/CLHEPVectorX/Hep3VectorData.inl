namespace MACE::Utility::CLHEPVectorX::Hep3VectorData {

#ifdef __cpp_lib_is_layout_compatible

namespace Internal {

class Hep3VectorImitator {
    double data[3];
};

} // namespace Internal

#endif

inline double* operator&(CLHEP::Hep3Vector& threeVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::Hep3Vector>);
    static_assert(sizeof(CLHEP::Hep3Vector) == 3 * sizeof(double));
    static_assert(alignof(CLHEP::Hep3Vector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Internal::Hep3VectorImitator>);
    static_assert(sizeof(Internal::Hep3VectorImitator) == 3 * sizeof(double));
    static_assert(alignof(Internal::Hep3VectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::Hep3Vector, Internal::Hep3VectorImitator>);
#endif
    return std::launder(reinterpret_cast<double*>(std::addressof(threeVector)));
}

inline const double* operator&(const CLHEP::Hep3Vector& threeVector) noexcept {
    static_assert(std::is_standard_layout_v<CLHEP::Hep3Vector>);
    static_assert(sizeof(CLHEP::Hep3Vector) == 3 * sizeof(double));
    static_assert(alignof(CLHEP::Hep3Vector) == alignof(double));
#ifdef __cpp_lib_is_layout_compatible
    static_assert(std::is_standard_layout_v<Internal::Hep3VectorImitator>);
    static_assert(sizeof(Internal::Hep3VectorImitator) == 3 * sizeof(double));
    static_assert(alignof(Internal::Hep3VectorImitator) == alignof(double));
    static_assert(std::is_layout_compatible_v<CLHEP::Hep3Vector, Internal::Hep3VectorImitator>);
#endif
    return std::launder(reinterpret_cast<const double*>(std::addressof(threeVector)));
}

} // namespace MACE::Utility::CLHEPHep3VectorData
