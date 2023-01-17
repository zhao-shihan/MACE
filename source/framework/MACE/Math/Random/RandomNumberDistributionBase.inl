namespace MACE::Math::Random {

template<class ADerived, class ADistribution>
constexpr DistributionParameterBase<ADerived, ADistribution>::DistributionParameterBase() {
    static_assert(DistributionParameterOf<ADerived, ADistribution>);
}

template<class ADerived, class AParameter, class T>
    requires(std::is_arithmetic_v<T> or Concept::NumericVectorAny<T>)
constexpr RandomNumberDistributionBase<ADerived, AParameter, T>::RandomNumberDistributionBase() {
    static_assert(RandomNumberDistribution<ADerived>);
}

} // namespace MACE::Math::Random
