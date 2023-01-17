namespace MACE::Math::Random::Distribution {

namespace internal {

template<std::floating_point T, template<typename> class AExponential>
constexpr BasicExponentialParameter<T, AExponential>::BasicExponentialParameter() :
    BasicExponentialParameter(1) {}

template<std::floating_point T, template<typename> class AExponential>
constexpr BasicExponentialParameter<T, AExponential>::BasicExponentialParameter(T expectation) :
    Base(),
    fExpectation(expectation) {}

template<std::floating_point T, template<typename> class AExponential, Concept::Character AChar>
auto operator<<(std::basic_ostream<AChar>& os, const BasicExponentialParameter<T, AExponential>& self) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
    return os << self.fExpectation << std::setprecision(oldPrecision);
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

} // namespace MACE::Math::Random::Distribution
