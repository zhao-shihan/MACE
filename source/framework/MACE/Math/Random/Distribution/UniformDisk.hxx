#pragma once

#include "MACE/Concept/InstantiatedFrom.hxx"
#include "MACE/Concept/MathVector.hxx"
#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"
#include "MACE/Math/Hypot.hxx"
#include "MACE/Math/IntegerPower.hxx"
#include "MACE/Math/Random/Distribution/UniformRectangle.hxx"
#include "MACE/Math/Random/RandomNumberDistributionBase.hxx"
#include "MACE/Utility/InlineMacro.hxx"
#include "MACE/Utility/VectorValueType.hxx"

#include <array>
#include <cmath>
#include <concepts>
#include <iomanip>

namespace MACE::Math::Random::inline Distribution {

namespace internal {

template<Concept::NumericVector2Any T, template<class> class AUniformDisk>
class BasicUniformDiskParameter final : public DistributionParameterBase<BasicUniformDiskParameter<T, AUniformDisk>,
                                                                         AUniformDisk<T>> {
private:
    using VT = VectorValueType<T>;
    using Base = DistributionParameterBase<BasicUniformDiskParameter<T, AUniformDisk>,
                                           AUniformDisk<T>>;

public:
    constexpr BasicUniformDiskParameter();
    constexpr BasicUniformDiskParameter(VT r, VT x0, VT y0);
    constexpr BasicUniformDiskParameter(VT radius, const T& center);
    constexpr explicit BasicUniformDiskParameter(VT radius);

    constexpr const auto& Radius() const { return fRadius; }
    constexpr const auto& CenterX() const { return fCenterX; }
    constexpr const auto& CenterY() const { return fCenterY; }
    constexpr T Center() const { return {fCenterX, fCenterY}; }

    constexpr void Radius(VT r) { fRadius = r; }
    constexpr void CenterX(VT x0) const { fCenterX = x0; }
    constexpr void CenterY(VT y0) const { fCenterY = y0; }
    constexpr void Center(VT x0, VT y0) { (CenterX(x0), CenterY(y0)); }
    constexpr void Center(const T& r0) { Center(r0[0], r0[1]); }

    template<Concept::Character AChar>
    friend auto operator<<(std::basic_ostream<AChar>& os, const BasicUniformDiskParameter<T, AUniformDisk>& self) -> decltype(os);
    template<Concept::Character AChar>
    friend auto operator>>(std::basic_istream<AChar>& is, BasicUniformDiskParameter<T, AUniformDisk>& self) -> decltype(is);

private:
    VT fRadius;
    VT fCenterX;
    VT fCenterY;
};

template<Concept::NumericVector2Any T, template<typename> class AUniformDisk>
class UniformDiskBase : public RandomNumberDistributionBase<AUniformDisk<T>,
                                                            BasicUniformDiskParameter<T, AUniformDisk>,
                                                            T> {
private:
    using VT = VectorValueType<T>;
    using Base = RandomNumberDistributionBase<AUniformDisk<T>,
                                              BasicUniformDiskParameter<T, AUniformDisk>,
                                              T>;

public:
    constexpr UniformDiskBase() = default;
    constexpr UniformDiskBase(VT r, VT x0, VT y0);
    constexpr UniformDiskBase(VT radius, const T& center);
    constexpr explicit UniformDiskBase(VT radius);
    constexpr explicit UniformDiskBase(const typename Base::ParameterType& p);

protected:
    constexpr ~UniformDiskBase() = default;

public:
    constexpr void Reset() {}

    constexpr auto Parameter() const { return fParameter; }
    constexpr const auto& Radius() const { return fParameter.Radius(); }
    constexpr const auto& CenterX() const { return fParameter.CenterX(); }
    constexpr const auto& CenterY() const { return fParameter.CenterY(); }
    constexpr auto Center() const { return fParameter.Center(); }

    constexpr void Parameter(const typename Base::ParameterType& p) { fParameter = p; }
    constexpr void Radius(VT r) { fParameter.Radius(r); }
    constexpr void CenterX(VT x0) const { fParameter.CenterX(x0); }
    constexpr void CenterY(VT y0) const { fParameter.CenterY(y0); }
    constexpr void Center(VT x0, VT y0) { fParameter.Center(x0, y0); }
    constexpr void Center(const T& r0) { fParameter.Center(r0); }

    constexpr auto Min() const { return T{CenterX() - Radius(), CenterY() - Radius()}; }
    constexpr auto Max() const { return T{CenterX() + Radius(), CenterY() + Radius()}; }

    static constexpr auto Stateless() { return true; }

    template<Concept::Character AChar>
    friend auto& operator<<(std::basic_ostream<AChar>& os, const UniformDiskBase<T, AUniformDisk>& self) { return os << self.fParameter; }
    template<Concept::Character AChar>
    friend auto& operator>>(std::basic_istream<AChar>& is, UniformDiskBase<T, AUniformDisk>& self) { return is >> self.fParameter; }

protected:
    static constexpr std::pair<T, VT> UniformCompactDisk(UniformRandomBitGenerator auto& g, const DistributionParameter auto& p);

protected:
    typename Base::ParameterType fParameter;
};

} // namespace internal

template<Concept::NumericVector2Any T = stdx::array2d>
class UniformCompactDisk;

template<Concept::NumericVector2Any T>
using UniformCompactDiskParameter = internal::BasicUniformDiskParameter<T, UniformCompactDisk>;

template<Concept::NumericVector2Any T>
class UniformCompactDisk final : public internal::UniformDiskBase<T, UniformCompactDisk> {
public:
    using internal::UniformDiskBase<T, UniformCompactDisk>::UniformDiskBase;

    MACE_STRONG_INLINE constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    MACE_STRONG_INLINE constexpr T operator()(UniformRandomBitGenerator auto& g, const UniformCompactDiskParameter<T>& p);
};

template<typename VT, class T>
UniformCompactDisk(VT, T) -> UniformCompactDisk<std::enable_if_t<std::same_as<VT, VectorValueType<std::remove_cvref_t<T>>>, std::remove_cvref_t<T>>>;
template<typename T, typename U, typename V>
UniformCompactDisk(T, U, V) -> UniformCompactDisk<std::array<std::common_type_t<T, U, V>, 2>>;
template<typename T>
UniformCompactDisk(T) -> UniformCompactDisk<std::array<T, 2>>;

template<Concept::NumericVector2Any T = stdx::array2d>
class UniformDisk;

template<Concept::NumericVector2Any T>
using UniformDiskParameter = internal::BasicUniformDiskParameter<T, UniformDisk>;

template<Concept::NumericVector2Any T>
class UniformDisk final : public internal::UniformDiskBase<T, UniformDisk> {
public:
    using internal::UniformDiskBase<T, UniformDisk>::UniformDiskBase;

    MACE_STRONG_INLINE constexpr auto operator()(UniformRandomBitGenerator auto& g) { return (*this)(g, this->fParameter); }
    MACE_STRONG_INLINE constexpr T operator()(UniformRandomBitGenerator auto& g, const UniformDiskParameter<T>& p);
};

template<typename VT, class T>
UniformDisk(VT, T) -> UniformDisk<std::enable_if_t<std::same_as<VT, VectorValueType<std::remove_cvref_t<T>>>, std::remove_cvref_t<T>>>;
template<typename T, typename U, typename V>
UniformDisk(T, U, V) -> UniformDisk<std::array<std::common_type_t<T, U, V>, 2>>;
template<typename T>
UniformDisk(T) -> UniformDisk<std::array<T, 2>>;

} // namespace MACE::Math::Random::inline Distribution

#include "MACE/Math/Random/Distribution/UniformDisk.inl"
