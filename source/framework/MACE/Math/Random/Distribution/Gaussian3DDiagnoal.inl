namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::NumericVector3FloatingPoint T, template<class> class AGaussian3DDiagnoal>
constexpr BasicGaussian3DDiagnoalParameter<T, AGaussian3DDiagnoal>::BasicGaussian3DDiagnoalParameter() :
    BasicGaussian3DDiagnoalParameter({0, 1},
                                     {0, 1},
                                     {0, 1}) {}

template<Concept::NumericVector3FloatingPoint T, template<class> class AGaussian3DDiagnoal>
constexpr BasicGaussian3DDiagnoalParameter<T, AGaussian3DDiagnoal>::BasicGaussian3DDiagnoalParameter(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY, std::pair<VOfT, VOfT> pZ) :
    Base(),
    fMuX(pX.first),
    fSigmaX(pX.second),
    fMuY(pY.first),
    fSigmaY(pY.second),
    fMuZ(pZ.first),
    fSigmaZ(pZ.second) {}

template<Concept::Character AChar, Concept::NumericVector3FloatingPoint U, template<class> class V>
auto operator<<(std::basic_ostream<AChar>& os, const BasicGaussian3DDiagnoalParameter<U, V>& self) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<U>::max_digits10);
    return os << self.fMuX << ' ' << self.fSigmaX << ' '
              << self.fMuY << ' ' << self.fSigmaY << ' '
              << self.fMuZ << ' ' << self.fSigmaZ
              << std::setprecision(oldPrecision);
}

template<Concept::Character AChar, Concept::NumericVector3FloatingPoint U, template<class> class V>
auto operator>>(std::basic_istream<AChar>& is, BasicGaussian3DDiagnoalParameter<U, V>& self) -> decltype(is) {
    return is >>
           self.fMuX >> self.fSigmaX >>
           self.fMuY >> self.fSigmaY >>
           self.fMuZ >> self.fSigmaZ;
}

template<template<class> class ADerived, Concept::NumericVector3FloatingPoint T>
constexpr Gaussian3DDiagnoalBase<ADerived, T>::Gaussian3DDiagnoalBase(std::pair<VOfT, VOfT> pX, std::pair<VOfT, VOfT> pY, std::pair<VOfT, VOfT> pZ) :
    Base(),
    fParameter(pX, pY, pZ) {}

template<template<class> class ADerived, Concept::NumericVector3FloatingPoint T>
constexpr Gaussian3DDiagnoalBase<ADerived, T>::Gaussian3DDiagnoalBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

} // namespace internal

#define MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_3D_DIAGNOAL_GENERATOR_SNIPPET(Suffix) \
    static_assert(Gaussian2DDiagnoal##Suffix<std::array<VOfT, 2>>::Stateless());     \
    Gaussian2DDiagnoal##Suffix<std::array<VOfT, 2>> standardGaussian2D;              \
    const auto&& [u, v] = standardGaussian2D(g);                                     \
    if ((fSaved = not fSaved)) {                                                     \
        const auto&& [w, x] = standardGaussian2D(g);                                 \
        fSavedValue = x;                                                             \
        return {p.SigmaX() * u + p.MuX(),                                            \
                p.SigmaY() * v + p.MuY(),                                            \
                p.SigmaZ() * w + p.MuZ()};                                           \
    } else {                                                                         \
        return {p.SigmaX() * u + p.MuX(),                                            \
                p.SigmaY() * v + p.MuY(),                                            \
                p.SigmaZ() * fSavedValue + p.MuZ()};                                 \
    }

template<Concept::NumericVector3FloatingPoint T>
T Gaussian3DDiagnoal<T>::operator()(UniformRandomBitGenerator auto& g, const Gaussian3DDiagnoalParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_3D_DIAGNOAL_GENERATOR_SNIPPET()
}

template<Concept::NumericVector3FloatingPoint T>
T Gaussian3DDiagnoalFast<T>::operator()(UniformRandomBitGenerator auto& g, const Gaussian3DDiagnoalFastParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_3D_DIAGNOAL_GENERATOR_SNIPPET(Fast)
}

#undef MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_3D_DIAGNOAL_GENERATOR_SNIPPET

} // namespace MACE::Math::Random::Distribution
