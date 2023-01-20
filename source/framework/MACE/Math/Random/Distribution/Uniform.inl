namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::Arithmetic T, template<typename> class AUniform>
constexpr BasicUniformParameter<T, AUniform>::BasicUniformParameter() :
    BasicUniformParameter(0, 1) {}

template<Concept::Arithmetic T, template<typename> class AUniform>
constexpr BasicUniformParameter<T, AUniform>::BasicUniformParameter(T inf, T sup) :
    DistributionParameterBase<BasicUniformParameter<T, AUniform>, AUniform<T>>(),
    fInfimum(inf),
    fSupremum(sup) {}

template<template<typename> class ADerived, Concept::Arithmetic T>
constexpr UniformBase<ADerived, T>::UniformBase(T inf, T sup) :
    Base(),
    fParameter(inf, sup) {}

template<template<typename> class ADerived, Concept::Arithmetic T>
constexpr UniformBase<ADerived, T>::UniformBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

template<template<typename> class ADerived, Concept::Arithmetic T, Concept::Character AChar>
auto operator<<(std::basic_ostream<AChar>& os, const UniformBase<ADerived, T>& self) -> decltype(os) {
    if constexpr (std::integral<T>) {
        return os << self.fParameter;
    } else {
        const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
        return os << self.fParameter << std::setprecision(oldPrecision);
    }
}

} // namespace internal

template<std::floating_point T>
constexpr T UniformCompact<T>::operator()(UniformRandomBitGenerator auto& g, const UniformCompactParameter<T>& p) {
    const auto u = static_cast<T>(g() - g.Min()) / (g.Max() - g.Min());
    std2b::assume(0 <= u and u <= 1);
    return p.Infimum() + u * (p.Supremum() - p.Infimum());
}

template<std::floating_point T>
constexpr T UniformReal<T>::operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p) {
    T u;
    do {
        u = UniformCompact()(g);
        std2b::assume(0 <= u and u <= 1);
    } while (u <= 0 or 1 <= u);
    return p.Infimum() + u * (p.Supremum() - p.Infimum());
}

template<std::integral T>
constexpr T UniformInteger<T>::operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p) {
    // Do we need an independent implementation?
    return std::uniform_int_distribution<T>(p.Infimum(), p.Supremum())(g);
}

} // namespace MACE::Math::Random::Distribution
