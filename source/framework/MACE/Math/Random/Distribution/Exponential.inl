namespace MACE::Math::Random::Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AExponential>
constexpr BasicExponentialParameter<T, AExponential>::BasicExponentialParameter() :
    BasicExponentialParameter(1) {}

template<std::floating_point T, template<typename> class AExponential>
constexpr BasicExponentialParameter<T, AExponential>::BasicExponentialParameter(T expectation) :
    DistributionParameterBase<BasicExponentialParameter<T, AExponential>, AExponential<T>>(),
    fExpectation(expectation) {}

template<std::floating_point T, template<typename> class AExponential>
constexpr ExponentialBase<T, AExponential>::ExponentialBase(T expectation) :
    RandomNumberDistributionBase<AExponential<T>, T, BasicExponentialParameter<T, AExponential>>(),
    fParameter(expectation) {}

template<std::floating_point T, template<typename> class AExponential>
constexpr ExponentialBase<T, AExponential>::ExponentialBase(BasicExponentialParameter<T, AExponential> p) :
    RandomNumberDistributionBase<AExponential<T>, T, BasicExponentialParameter<T, AExponential>>(),
    fParameter(p) {}

template<Concept::Character AChar, std::floating_point T, template<typename> class AExponential>
auto operator<<(std::basic_ostream<AChar>& os, const ExponentialBase<T, AExponential>& e) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
    return os << e.Expectation() << std::setprecision(oldPrecision);
}

template<Concept::Character AChar, std::floating_point T, template<typename> class AExponential>
auto operator>>(std::basic_istream<AChar>& is, ExponentialBase<T, AExponential>& e) -> decltype(is) {
    T expectation;
    is >> expectation;
    e.Expectation(expectation);
    return is;
}

} // namespace internal

template<std::floating_point T>
constexpr T Exponential<T>::operator()(UniformRandomBitGenerator auto& g, ExponentialParameter<T> p) {
    return -std::log(CompactUniform()(g)) * p.Expectation();
}

} // namespace MACE::Math::Random::Distribution
