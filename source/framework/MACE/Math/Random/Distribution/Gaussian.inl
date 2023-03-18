namespace MACE::Math::Random::Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AGaussian>
constexpr BasicGaussianParameter<T, AGaussian>::BasicGaussianParameter() :
    BasicGaussianParameter(0, 1) {}

template<std::floating_point T, template<typename> class AGaussian>
constexpr BasicGaussianParameter<T, AGaussian>::BasicGaussianParameter(T mu, T sigma) :
    Base(),
    fMu(mu),
    fSigma(sigma) {}

template<Concept::Character AChar, std::floating_point U, template<typename> class V>
auto operator<<(std::basic_ostream<AChar>& os, const BasicGaussianParameter<U, V>& self) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<U>::max_digits10);
    return os << self.fMu << ' ' << self.fSigma
              << std::setprecision(oldPrecision);
}

template<Concept::Character AChar, std::floating_point U, template<typename> class V>
auto operator>>(std::basic_istream<AChar>& is, BasicGaussianParameter<U, V>& self) -> decltype(is) {
    return is >> self.fMu >> self.fSigma;
}

template<std::floating_point T, template<typename> class AGaussian>
constexpr GaussianBase<T, AGaussian>::GaussianBase(T mu, T sigma) :
    Base(),
    fParameter(mu, sigma) {}

template<std::floating_point T, template<typename> class AGaussian>
constexpr GaussianBase<T, AGaussian>::GaussianBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

} // namespace internal

#define MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_GENERATOR_SNIPPET(Suffix)          \
    if ((fSaved = not fSaved)) {                                                  \
        static_assert(Gaussian2DDiagnoal##Suffix<std::array<T, 2>>::Stateless()); \
        const auto&& [u, v] = Gaussian2DDiagnoal##Suffix<std::array<T, 2>>()(g);  \
        fSavedValue = v;                                                          \
        return p.Sigma() * u + p.Mu();                                            \
    } else {                                                                      \
        return p.Sigma() * fSavedValue + p.Mu();                                  \
    }

template<std::floating_point T>
T Gaussian<T>::operator()(UniformRandomBitGenerator auto& g, const GaussianParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_GENERATOR_SNIPPET()
}

template<std::floating_point T>
T GaussianFast<T>::operator()(UniformRandomBitGenerator auto& g, const GaussianFastParameter<T>& p) {
    MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_GENERATOR_SNIPPET(Fast)
}

#undef MACE_MATH_RANDOM_DISTRIBUTION_GAUSSIAN_GENERATOR_SNIPPET

} // namespace MACE::Math::Random::Distribution
