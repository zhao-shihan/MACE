#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Extension/gslx/index_sequence.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"

#include "gsl/gsl"

#include <array>
#include <concepts>
#include <tuple>
#include <type_traits>
#include <utility>

namespace MACE::Math::Random::Distribution {

namespace internal {

namespace internal {

template<gsl::index I, class T>
struct Margin {
    T value;
};

template<class...>
struct CartesianProductMarginBase;
template<gsl::index... Is, class... Ts>
    requires(sizeof...(Is) == sizeof...(Ts))
struct CartesianProductMarginBase<gslx::index_sequence<Is...>, Ts...> : Margin<Is, Ts>... {};

} // namespace internal

template<class... Ts>
struct CartesianProductMargin : internal::CartesianProductMarginBase<gslx::index_sequence_for<Ts...>, Ts...> {
    CartesianProductMargin() = default;
    CartesianProductMargin(const Ts&... objects);

    template<gsl::index I>
    constexpr const auto& Margin() const { return static_cast<const internal::Margin<I, std::tuple_element_t<I, std::tuple<Ts...>>>*>(this)->value; }
    template<gsl::index I>
    constexpr auto& Margin() { return static_cast<internal::Margin<I, std::tuple_element_t<I, std::tuple<Ts...>>>*>(this)->value; }
};

} // namespace internal

template<class ADerived, class ADistribution, class... Ds>
    requires(sizeof...(Ds) >= 2)
class JointParameterInterface : public DistributionParameterBase<ADerived, ADistribution>,
                                public internal::CartesianProductMargin<typename Ds::ParameterType...> {
public:
    constexpr JointParameterInterface();
    constexpr JointParameterInterface(const typename Ds::ParameterType&... p);

protected:
    constexpr ~JointParameterInterface() = default;

public:
    template<gsl::index I>
    constexpr const auto& Parameter() const { return this->template Margin<I>(); }

    template<gsl::index I>
    constexpr void Parameter(const std::tuple_element_t<I, std::tuple<typename Ds::ParameterType...>>& p) { this->template Margin<I>() = p; }

    template<Concept::Character AChar, class U, class V, class... Ws>
    friend auto operator<<(std::basic_ostream<AChar>& os, const JointParameterInterface<U, V, Ws...>& self) -> decltype(os);
    template<Concept::Character AChar, class U, class V, class... Ws>
    friend auto operator>>(std::basic_istream<AChar>& is, JointParameterInterface<U, V, Ws...>& self) -> decltype(is);
};

template<class ADerived, class AParameter, class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)>)
class JointInterface : public RandomNumberDistributionBase<ADerived, AParameter, T>,
                       public internal::CartesianProductMargin<Ds...> {
public:
    constexpr JointInterface();
    constexpr JointInterface(const typename Ds::ParameterType&... p);
    constexpr explicit JointInterface(const AParameter& p);

protected:
    constexpr ~JointInterface() = default;

public:
    constexpr T operator()(UniformRandomBitGenerator auto& g);
    constexpr T operator()(UniformRandomBitGenerator auto& g, const AParameter& p);

    constexpr void Reset();

    constexpr AParameter Parameter() const;
    template<gsl::index I>
    constexpr auto Parameter() const { return this->template Margin<I>().Parameter(); }

    constexpr void Parameter(const AParameter& p);
    template<gsl::index I>
    constexpr void Parameter(const typename std::tuple_element_t<I, std::tuple<Ds...>>::ParameterType& p) { this->template Margin<I>().Parameter(p); }

    constexpr T Min() const;
    constexpr T Max() const;

    static constexpr bool Stateless() { return (... and Ds::Stateless()); }

    template<Concept::Character AChar>
    friend auto operator<<(std::basic_ostream<AChar>& os, const JointInterface& self) -> decltype(os);
    template<Concept::Character AChar>
    friend auto operator>>(std::basic_istream<AChar>& is, JointInterface& self) -> decltype(is);
};

template<class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)> and (... and Concept::Arithmetic<typename Ds::ResultType>))
class Joint;

template<class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)> and (... and Concept::Arithmetic<typename Ds::ResultType>))
class JointParameter final : public JointParameterInterface<JointParameter<T, Ds...>,
                                                            Joint<T, Ds...>,
                                                            Ds...> {
    using JointParameterInterface<Ds...>::JointParameterInterface;
};

template<class... Ps>
JointParameter(Ps...) -> JointParameter<std::array<std::common_type_t<typename Ps::DistributionType::ResultType...>, sizeof...(Ps)>, typename Ps::DistributionType...>;

template<class T, class... Ds>
    requires(sizeof...(Ds) >= 2 and Concept::NumericVectorAny<T, sizeof...(Ds)> and (... and Concept::Arithmetic<typename Ds::ResultType>))
class Joint final : public JointInterface<Joint<T, Ds...>,
                                          JointParameter<T, Ds...>,
                                          T,
                                          Ds...> {
    using JointInterface<T, Ds...>::JointInterface;
};

template<class... Ps>
Joint(Ps...) -> Joint<std::array<std::common_type_t<typename Ps::DistributionType::ResultType...>, sizeof...(Ps)>, typename Ps::DistributionType...>;
template<class... Ds>
Joint(JointParameter<Ds...>) -> Joint<std::array<std::common_type_t<typename Ds::ResultType...>, sizeof...(Ds)>, Ds...>;

} // namespace MACE::Math::Random::Distribution

#include "MACE/Math/Random/Distribution/Joint.inl"
