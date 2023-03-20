namespace MACE::Math::Random::inline Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AExponential>
constexpr BasicExponentialParameter<T, AExponential>::BasicExponentialParameter() :
    BasicExponentialParameter(1) {}

template<std::floating_point T, template<typename> class AExponential>
constexpr BasicExponentialParameter<T, AExponential>::BasicExponentialParameter(T expectation) :
    Base(),
    fExpectation(expectation) {}

template<Concept::Character AChar, std::floating_point U, template<typename> class V>
auto operator<<(std::basic_ostream<AChar>& os, const BasicExponentialParameter<U, V>& self) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<U>::max_digits10);
    return os << self.fExpectation
              << std::setprecision(oldPrecision);
}

template<Concept::Character AChar, std::floating_point U, template<typename> class V>
auto operator>>(std::basic_istream<AChar>& is, BasicExponentialParameter<U, V>& self) -> decltype(is) {
    return is >> self.fExpectation;
}

template<template<typename> class ADerived, std::floating_point T>
constexpr ExponentialBase<ADerived, T>::ExponentialBase(T expectation) :
    Base(),
    fParameter(expectation) {}

template<template<typename> class ADerived, std::floating_point T>
constexpr ExponentialBase<ADerived, T>::ExponentialBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

} // namespace internal

template<std::floating_point T>
constexpr T Exponential<T>::operator()(UniformRandomBitGenerator auto& g, const ExponentialParameter<T>& p) {
    return -p.Expectation() * Math::Log(Uniform<T>()(g));
}

template<std::floating_point T>
constexpr T ExponentialFast<T>::operator()(UniformRandomBitGenerator auto& g, const ExponentialFastParameter<T>& p) {
    return -p.Expectation() * Math::RA2Log(Uniform<T>()(g));
}

} // namespace MACE::Math::Random::inline Distribution
