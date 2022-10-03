namespace MACE::Math::Random::Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AGaussian>
constexpr BasicGaussianParameter<T, AGaussian>::BasicGaussianParameter() :
    BasicGaussianParameter(0, 1) {}

template<std::floating_point T, template<typename> class AGaussian>
constexpr BasicGaussianParameter<T, AGaussian>::BasicGaussianParameter(T mu, T sigma) :
    DistributionParameterBase<BasicGaussianParameter<T, AGaussian>, AGaussian<T>>(),
    fMu(mu),
    fSigma(sigma) {}

template<std::floating_point T, template<typename> class AGaussian>
constexpr GaussianBase<T, AGaussian>::GaussianBase(T mu, T sigma) :
    RandomNumberDistributionBase<AGaussian<T>, T, BasicGaussianParameter<T, AGaussian>>(),
    fParameter(mu, sigma) {}

template<std::floating_point T, template<typename> class AGaussian>
constexpr GaussianBase<T, AGaussian>::GaussianBase(const BasicGaussianParameter<T, AGaussian>& p) :
    RandomNumberDistributionBase<AGaussian<T>, T, BasicGaussianParameter<T, AGaussian>>(),
    fParameter(p) {}

template<Concept::Character AChar, std::floating_point T, template<typename> class AGaussian>
auto operator<<(std::basic_ostream<AChar>& os, const GaussianBase<T, AGaussian>& g) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
    return os << g.Mu() << ' ' << g.Sigma() << std::setprecision(oldPrecision);
}

template<Concept::Character AChar, Concept::Arithmetic T, template<typename> class AGaussian>
auto operator>>(std::basic_istream<AChar>& is, GaussianBase<T, AGaussian>& g) -> decltype(is) {
    T mu;
    T sigma;
    is >> mu >> sigma;
    g.Mu(mu);
    g.Sigma(sigma);
    return is;
}

} // namespace internal

template<std::floating_point T>
constexpr T Gaussian<T>::operator()(UniformRandomBitGenerator auto& g, const GaussianParameter<T>& p) {

}

} // namespace MACE::Math::Random::Distribution
