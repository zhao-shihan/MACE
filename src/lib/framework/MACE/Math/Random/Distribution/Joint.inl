namespace MACE::Math::Random::inline Distribution {

namespace internal {

template<class... Ts>
CartesianProductMargin<Ts...>::CartesianProductMargin(const Ts&... objects) :
    internal::CartesianProductMarginBase<gslx::index_sequence_for<Ts...>, Ts...>{{objects}...} {}

} // namespace internal

template<class ADerived, class ADistribution, class... Ds>
    requires(sizeof...(Ds) >= 2)
constexpr JointParameterInterface<ADerived, ADistribution, Ds...>::JointParameterInterface() :
    DistributionParameterBase<ADerived, ADistribution>(),
    internal::CartesianProductMargin<typename Ds::ParameterType...>() {
    static_assert(std::derived_from<ADerived, JointParameterInterface<ADerived, ADistribution, Ds...>>);
}

template<class ADerived, class ADistribution, class... Ds>
    requires(sizeof...(Ds) >= 2)
constexpr JointParameterInterface<ADerived, ADistribution, Ds...>::JointParameterInterface(const typename Ds::ParameterType&... p) :
    DistributionParameterBase<ADerived, ADistribution>(),
    internal::CartesianProductMargin<typename Ds::ParameterType...>(p...) {}

template<Concept::Character AChar, class U, class V, class... Ws>
auto operator<<(std::basic_ostream<AChar>& os, const JointParameterInterface<U, V, Ws...>& self) -> decltype(os) {
    return ([&os, &self]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return (os << ... << self.template Margin<Is>());
    })(gslx::index_sequence_for<Ws...>());
}

template<Concept::Character AChar, class U, class V, class... Ws>
auto operator>>(std::basic_istream<AChar>& is, JointParameterInterface<U, V, Ws...>& self) -> decltype(is) {
    return ([&is, &self]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return (is >> ... >> self.template Margin<Is>());
    })(gslx::index_sequence_for<Ws...>());
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr JointInterface<ADerived, AParameter, T, Ds...>::JointInterface() :
    RandomNumberDistributionBase<ADerived, AParameter, T>(),
    internal::CartesianProductMargin<Ds...>() {
    static_assert(std::derived_from<ADerived, JointInterface<ADerived, AParameter, T, Ds...>>);
    static_assert(std::derived_from<AParameter, JointParameterInterface<AParameter, ADerived, Ds...>>);
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr JointInterface<ADerived, AParameter, T, Ds...>::JointInterface(const typename Ds::ParameterType&... p) :
    RandomNumberDistributionBase<ADerived, AParameter, T>(),
    internal::CartesianProductMargin<Ds...>(Ds(p)...) {}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr JointInterface<ADerived, AParameter, T, Ds...>::JointInterface(const AParameter& p) :
    RandomNumberDistributionBase<ADerived, AParameter, T>(),
    internal::CartesianProductMargin<Ds...>(std::make_from_tuple<internal::CartesianProductMargin<Ds...>>(p)) {}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
MACE_STRONG_INLINE constexpr T JointInterface<ADerived, AParameter, T, Ds...>::operator()(UniformRandomBitGenerator auto& g) {
    return ([this, &g]<gsl::index... Is>(gslx::index_sequence<Is...>)->T {
        return {this->template Margin<Is>()(g)...};
    })(gslx::index_sequence_for<Ds...>());
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
MACE_STRONG_INLINE constexpr T JointInterface<ADerived, AParameter, T, Ds...>::operator()(UniformRandomBitGenerator auto& g, const AParameter& p) {
    return ([this, &g, &p]<gsl::index... Is>(gslx::index_sequence<Is...>)->T {
        return {this->template Margin<Is>()(g, p.template Parameter<Is>())...};
    })(gslx::index_sequence_for<Ds...>());
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr void JointInterface<ADerived, AParameter, T, Ds...>::Reset() {
    ([this]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        (..., this->template Margin<Is>().Reset());
    })(gslx::index_sequence_for<Ds...>());
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr AParameter JointInterface<ADerived, AParameter, T, Ds...>::Parameter() const {
    return ([this]<gsl::index... Is>(gslx::index_sequence<Is...>)->AParameter {
        return {this->Parameter<Is>()...};
    })(gslx::index_sequence_for<Ds...>());
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr void JointInterface<ADerived, AParameter, T, Ds...>::Parameter(const AParameter& p) {
    ([this, &p]<gsl::index... Is>(std::index_sequence<Is...>) {
        (..., this->Parameter<Is>(p.template Parameter<Is>()));
    })(gslx::index_sequence_for<Ds...>());
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr T JointInterface<ADerived, AParameter, T, Ds...>::Min() const {
    return ([this]<gsl::index... Is>(gslx::index_sequence<Is...>)->T {
        return {this->template Margin<Is>().Min()...};
    })(gslx::index_sequence_for<Ds...>());
}

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
constexpr T JointInterface<ADerived, AParameter, T, Ds...>::Max() const {
    return ([this]<gsl::index... Is>(gslx::index_sequence<Is...>)->T {
        return {this->template Margin<Is>().Max()...};
    })(gslx::index_sequence_for<Ds...>());
}

template<class... Ds, Concept::Character AChar>
auto operator<<(std::basic_ostream<AChar>& os, const JointInterface<Ds...>& self) -> decltype(os) {
    return ([&os, &self]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return (os << ... << self.template Margin<Is>());
    })(gslx::index_sequence_for<Ds...>());
}

template<class... Ds, Concept::Character AChar>
auto operator>>(std::basic_istream<AChar>& is, JointInterface<Ds...>& self) -> decltype(is) {
    return ([&is, &self]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return (is >> ... >> self.template Margin<Is>());
    })(gslx::index_sequence_for<Ds...>());
}

} // namespace MACE::Math::Random::inline Distribution
