namespace MACE::Math::Random::Distribution {

template<std::floating_point T>
constexpr UniformParameter<T>::UniformParameter() :
    DistributionParameterBase<UniformParameter<T>, Uniform<T>>(),
    fInfimum(0),
    fSupremum(1) {}

template<std::floating_point T>
constexpr UniformParameter<T>::UniformParameter(T inf, T sup) :
    DistributionParameterBase<UniformParameter<T>, Uniform<T>>(),
    fInfimum(inf),
    fSupremum(sup) {}

template<std::floating_point T>
constexpr Uniform<T>::Uniform(T inf, T sup) :
    RandomNumberDistributionBase<Uniform<T>, T, UniformParameter<T>>(),
    fParameter(inf, sup) {}

template<std::floating_point T>
constexpr Uniform<T>::Uniform(const UniformParameter<T>& p) :
    RandomNumberDistributionBase<Uniform<T>, T, UniformParameter<T>>(),
    fParameter(p) {}

template<std::floating_point T>
constexpr T Uniform<T>::operator()(UniformRandomBitGenerator auto& g, const UniformParameter<T>& p) {
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

template<std::floating_point T>
auto operator<<(Concept::InstantiatedFrom<std::basic_ostream> auto& os, const Uniform<T>& d) -> decltype(os) {
    const auto oldPrecision = os.precision(std::numeric_limits<T>::max_digits10);
    os << d.Infimum() << ' ' << d.Supremum();
    os.precision(oldPrecision);
    return os;
}

template<std::floating_point T>
auto operator>>(Concept::InstantiatedFrom<std::basic_istream> auto& is, Uniform<T>& d) -> decltype(is) {
    T inf;
    T sup;
    is >> inf >> ' ' >> sup;
    d.Infimum(inf);
    d.Supremum(sup);
    return is;
}

} // namespace MACE::Math::Random::Distribution
