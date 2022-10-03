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

template<Concept::Arithmetic T, template<typename> class AUniform>
constexpr UniformBase<T, AUniform>::UniformBase(T inf, T sup) :
    RandomNumberDistributionBase<AUniform<T>, T, BasicUniformParameter<T, AUniform>>(),
    fParameter(inf, sup) {}

template<Concept::Arithmetic T, template<typename> class AUniform>
constexpr UniformBase<T, AUniform>::UniformBase(BasicUniformParameter<T, AUniform> p) :
    RandomNumberDistributionBase<AUniform<T>, T, BasicUniformParameter<T, AUniform>>(),
    fParameter(p) {}

template<Concept::Character AChar, Concept::Arithmetic T, template<typename> class AUniform>
auto operator<<(std::basic_ostream<AChar>& os, const UniformBase<T, AUniform>& u) -> decltype(os) {
    if constexpr (std::integral<T>) {
        return os << u.Infimum() << ' ' << u.Supremum();
    } else {
        const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
        return os << u.Infimum() << ' ' << u.Supremum() << std::setprecision(oldPrecision);
    }
}

template<Concept::Character AChar, Concept::Arithmetic T, template<typename> class AUniform>
auto operator>>(std::basic_istream<AChar>& is, UniformBase<T, AUniform>& u) -> decltype(is) {
    T inf;
    T sup;
    is >> inf >> sup;
    u.Infimum(inf);
    u.Supremum(sup);
    return is;
}

} // namespace internal

template<std::floating_point T>
constexpr T CompactUniform<T>::operator()(UniformRandomBitGenerator auto& g, CompactUniformParameter<T> p) {
    const auto u = (g() - g.Min()) * static_cast<T>(1 / static_cast<long double>(g.Max() - g.Min()));
    return p.Infimum() * (1 - u) + p.Supremum() * u;
}

template<std::floating_point T>
constexpr T UniformReal<T>::operator()(UniformRandomBitGenerator auto& g, UniformParameter<T> p) {
    const auto inf = p.Infimum();
    const auto sup = p.Supremum();
    T x;
    do {
        x = CompactUniform(inf, sup)(g);
    } while (x <= inf || sup <= x);
    return x;
}

template<std::integral T>
constexpr T UniformInteger<T>::operator()(UniformRandomBitGenerator auto& g, UniformParameter<T> p) {
    // TODO: a better implementation
    return std::uniform_int_distribution<T>(p.Infimum(), p.Supremum())(g);
}

} // namespace MACE::Math::Random::Distribution
