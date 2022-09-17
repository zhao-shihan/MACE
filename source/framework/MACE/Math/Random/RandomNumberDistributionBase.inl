namespace MACE::Math::Random {

template<class ADerived, class ADistribution>
constexpr DistributionParameterBase<ADerived, ADistribution>::DistributionParameterBase() {
    static_assert(DistributionParameterOf<ADerived, ADistribution>);
}

template<class ADerived, Concept::Arithmetic AResult, class AParameter>
constexpr RandomNumberDistributionBase<ADerived, AResult, AParameter>::RandomNumberDistributionBase() {
    static_assert(RandomNumberDistribution<ADerived>);
}

} // namespace MACE::Math::Random
