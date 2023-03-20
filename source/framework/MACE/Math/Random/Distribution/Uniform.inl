namespace MACE::Math::Random::Distribution {

namespace internal {

template<Concept::Arithmetic T, template<typename> class AUniform>
constexpr BasicUniformParameter<T, AUniform>::BasicUniformParameter() :
    BasicUniformParameter(0,
                          std::integral<T> ?
                              std::numeric_limits<T>::max() :
                              1) {}

template<Concept::Arithmetic T, template<typename> class AUniform>
constexpr BasicUniformParameter<T, AUniform>::BasicUniformParameter(T inf, T sup) :
    DistributionParameterBase<BasicUniformParameter<T, AUniform>, AUniform<T>>(),
    fInfimum(inf),
    fSupremum(sup) {}

template<Concept::Character AChar, Concept::Arithmetic U, template<typename> class V>
auto operator<<(std::basic_ostream<AChar>& os, const BasicUniformParameter<U, V>& self) -> decltype(os) {
    if constexpr (std::floating_point<U>) {
        const auto oldPrecision = os.precision(std::numeric_limits<U>::max_digits10);
        return os << self.fInfimum << ' ' << self.fSupremum
                  << std::setprecision(oldPrecision);
    } else {
        return os << self.fInfimum << ' ' << self.fSupremum;
    }
}

template<Concept::Character AChar, Concept::Arithmetic U, template<typename> class V>
auto operator>>(std::basic_istream<AChar>& is, BasicUniformParameter<U, V>& self) -> decltype(is) {
    return is >> self.fInfimum >> self.fSupremum;
}

template<template<typename> class ADerived, Concept::Arithmetic T>
constexpr UniformBase<ADerived, T>::UniformBase(T inf, T sup) :
    Base(),
    fParameter(inf, sup) {}

template<template<typename> class ADerived, Concept::Arithmetic T>
constexpr UniformBase<ADerived, T>::UniformBase(const typename Base::ParameterType& p) :
    Base(),
    fParameter(p) {}

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
