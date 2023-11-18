namespace MACE::Math::Random::inline Distribution {

namespace internal {

template<Concept::NumericVector2FloatingPoint T, template<typename> typename AGaussian2DDiagnoal>
constexpr BasicGaussian2DDiagnoalParameter<T, AGaussian2DDiagnoal>::BasicGaussian2DDiagnoalParameter() :
    BasicGaussian2DDiagnoalParameter({0, 1},
                                     {0, 1}) {}

template<Concept::NumericVector2FloatingPoint T, template<typename> typename AGaussian2DDiagnoal>
constexpr BasicGaussian2DDiagnoalParameter<T, AGaussian2DDiagnoal>::BasicGaussian2DDiagnoalParameter(std::pair<VT, VT> pX, std::pair<VT, VT> pY) :
    Base(),
    fMuX(pX.first),
    fSigmaX(pX.second),
    fMuY(pY.first),
    fSigmaY(pY.second) {}

template<Concept::Character AChar, Concept::NumericVector2FloatingPoint U, template<typename> typename V>
auto operator<<(std::basic_ostream<AChar>& os, const BasicGaussian2DDiagnoalParameter<U, V>& self) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<U>::max_digits10);
    return os << self.fMuX << ' ' << self.fSigmaX << ' ' << self.fMuY << ' ' << self.fSigmaY
              << std::setprecision(oldPrecision);
}

template<Concept::Character AChar, Concept::NumericVector2FloatingPoint U, template<typename> typename V>
auto operator>>(std::basic_istream<AChar>& is, BasicGaussian2DDiagnoalParameter<U, V>& self) -> decltype(is) {
    return is >> self.fMuX >> self.fSigmaX >> self.fMuY >> self.fSigmaY;
}

template<template<typename> typename ADerived, Concept::NumericVector2FloatingPoint T>
constexpr Gaussian2DDiagnoalBase<ADerived, T>::Gaussian2DDiagnoalBase(std::pair<VT, VT> pX, std::pair<VT, VT> pY) :
    Base(),
    fParameter(pX, pY) {}

template<template<typename> typename ADerived, Concept::NumericVector2FloatingPoint T>
constexpr Gaussian2DDiagnoalBase<ADerived, T>::Gaussian2DDiagnoalBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

} // namespace internal

#define MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET(TheLog) \
    T u;                                                                             \
    VT x;                                                                            \
    do {                                                                             \
        static_assert(UniformCompactRectangle<T>::Stateless());                      \
        u = UniformCompactRectangle<T>({-0.5, 0.5}, {-0.5, 0.5})(g);                 \
        x = Math::Hypot2(u[0], u[1]);                                                \
        std2b::assume(0 <= x and x < 0.5);                                           \
    } while (x == 0 or x > 0.25);                                                    \
    x = std::sqrt(-2 * (TheLog(x) + 2 * std::numbers::ln2_v<VT>) / x);               \
    u[0] = p.SigmaX() * (x * u[0]) + p.MuX();                                        \
    u[1] = p.SigmaY() * (x * u[1]) + p.MuY();                                        \
    return u;

template<Concept::NumericVector2FloatingPoint T>
MACE_STRONG_INLINE T Gaussian2DDiagnoal<T>::operator()(UniformRandomBitGenerator auto& g, const Gaussian2DDiagnoalParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET(Math::Log)
}

template<Concept::NumericVector2FloatingPoint T>
MACE_STRONG_INLINE T Gaussian2DDiagnoalFast<T>::operator()(UniformRandomBitGenerator auto& g, const Gaussian2DDiagnoalFastParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET(internal::FastLogForCompact01)
}

#undef MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET

} // namespace MACE::Math::Random::inline Distribution
