namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::NumericVector2FloatingPoint T, template<class> class AGaussian2DDiagnoal>
constexpr BasicGaussian2DDiagnoalParameter<T, AGaussian2DDiagnoal>::BasicGaussian2DDiagnoalParameter() :
    BasicGaussian2DDiagnoalParameter({0, 1},
                                     {0, 1}) {}

template<Concept::NumericVector2FloatingPoint T, template<class> class AGaussian2DDiagnoal>
constexpr BasicGaussian2DDiagnoalParameter<T, AGaussian2DDiagnoal>::BasicGaussian2DDiagnoalParameter(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY) :
    Base(),
    fMuX(pX.first),
    fSigmaX(pX.second),
    fMuY(pY.first),
    fSigmaY(pY.second) {}

template<std::floating_point T, template<typename> class AGaussian2D, Concept::Character AChar>
auto operator<<(std::basic_ostream<AChar>& os, BasicGaussian2DDiagnoalParameter<T, AGaussian2D> self) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
    return os << self.fMuX << ' ' << self.fSigmaX << ' ' << self.fMuY << ' ' << self.fSigmaY
              << std::setprecision(oldPrecision);
}

template<std::floating_point T, template<typename> class AGaussian2D, Concept::Character AChar>
auto operator>>(std::basic_ostream<AChar>& is, BasicGaussian2DDiagnoalParameter<T, AGaussian2D> self) -> decltype(is) {
    return is >> self.fMuX >> self.fSigmaX >> self.fMuY >> self.fSigmaY;
}

template<template<class> class ADerived, Concept::NumericVector2FloatingPoint T>
constexpr Gaussian2DDiagnoalBase<ADerived, T>::Gaussian2DDiagnoalBase(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY) :
    Base(),
    fParameter(pX, pY) {}

template<template<class> class ADerived, Concept::NumericVector2FloatingPoint T>
constexpr Gaussian2DDiagnoalBase<ADerived, T>::Gaussian2DDiagnoalBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

} // namespace internal

#define MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET(TheLog) \
    T u;                                                                             \
    VOfT x;                                                                          \
    do {                                                                             \
        static_assert(UniformCompactRectangle<T>::Stateless());                      \
        u = UniformCompactRectangle<T>({-0.5, 0.5}, {-0.5, 0.5})(g);                 \
        x = Math::Hypot2(u[0], u[1]);                                                \
        std2b::assume(0 <= x and x <= 0.5);                                          \
    } while (x == 0 or x > 0.25);                                                    \
    x = std::sqrt(-2 * (Math::TheLog(x) + 2 * std::numbers::ln2_v<VOfT>) / x);       \
    u[0] = p.SigmaX() * (x * u[0]) + p.MuX();                                        \
    u[1] = p.SigmaY() * (x * u[1]) + p.MuY();                                        \
    return u;

template<Concept::NumericVector2FloatingPoint T>
T Gaussian2DDiagnoal<T>::operator()(UniformRandomBitGenerator auto& g, const Gaussian2DDiagnoalParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET(Log)
}

template<Concept::NumericVector2FloatingPoint T>
T Gaussian2DDiagnoalFast<T>::operator()(UniformRandomBitGenerator auto& g, const Gaussian2DDiagnoalFastParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET(RA2Log)
}

#undef MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_2D_DIAGNOAL_GENERATOR_SNIPPET

} // namespace MACE::Math::Random::Distribution
