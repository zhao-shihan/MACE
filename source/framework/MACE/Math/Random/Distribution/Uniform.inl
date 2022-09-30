namespace MACE::Math::Random::Distribution {

template<Concept::Arithmetic T>
constexpr UniformParameter<T>::UniformParameter() :
    UniformParameter(0, 1) {}

template<Concept::Arithmetic T>
constexpr UniformParameter<T>::UniformParameter(T inf, T sup) :
    DistributionParameterBase<UniformParameter<T>, Uniform<T>>(),
    fInfimum(inf),
    fSupremum(sup) {}

namespace internal {

template<Concept::Arithmetic T>
constexpr UniformBase<T>::UniformBase(T inf, T sup) :
    RandomNumberDistributionBase<Uniform<T>, T, UniformParameter<T>>(),
    fParameter(inf, sup) {}

template<Concept::Arithmetic T>
constexpr UniformBase<T>::UniformBase(const UniformParameter<T>& p) :
    RandomNumberDistributionBase<Uniform<T>, T, UniformParameter<T>>(),
    fParameter(p) {}

template<Concept::Character AChar, Concept::Arithmetic T>
auto operator<<(std::basic_ostream<AChar>& os, const UniformBase<T>& u) -> decltype(os) {
    if constexpr (std::integral<T>) {
        return os << u.Infimum() << ' ' << u.Supremum();
    } else {
        const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
        return os << u.Infimum() << ' ' << u.Supremum() << std::setprecision(oldPrecision);
    }
}

template<Concept::Character AChar, Concept::Arithmetic T>
auto operator>>(std::basic_istream<AChar>& is, UniformBase<T>& u) -> decltype(is) {
    T inf;
    T sup;
    is >> inf >> sup;
    u.Infimum(inf);
    u.Supremum(sup);
    return is;
}

} // namespace internal

template<std::floating_point T>
constexpr T UniformReal<T>::operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p) {
    const auto inf = p.Infimum();
    const auto sup = p.Supremum();
    T x;
    do {
        const auto u = (g() - g.Min()) *
                       static_cast<T>(1 / static_cast<long double>(g.Max() - g.Min()));
        x = inf * (1 - u) + sup * u;
    } while (x <= inf || sup <= x);
    return x;
}

template<std::integral T>
constexpr T UniformInteger<T>::operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p) {
    // TODO: a better implementation
    return std::uniform_int_distribution<T>(p.Infimum(), p.Supremum())(g);
}

} // namespace MACE::Math::Random::Distribution
