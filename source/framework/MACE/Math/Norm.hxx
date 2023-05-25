#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Extension/gslx/index_sequence.hxx"
#include "MACE/Math/Hypot.hxx"
#include "MACE/Utility/ToSigned.hxx"
#include "MACE/Utility/VectorCast.hxx"
#include "MACE/Utility/VectorDimension.hxx"
#include "MACE/Utility/VectorValueType.hxx"

#include "gsl/gsl"

#include <cmath>
#include <concepts>
#include <type_traits>

namespace MACE::Math {

constexpr auto Norm2(const Concept::NumericVectorFloatingPoint auto& x) {
    return ([&x]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return Hypot2(x[Is]...);
    })(gslx::make_index_sequence<VectorDimension<std::decay_t<decltype(x)>>>());
}

auto Norm(const Concept::NumericVectorFloatingPoint auto& x) {
    return std::sqrt(Norm2(x));
}

template<std::floating_point T = double>
constexpr auto Norm2(const Concept::NumericVectorIntegral auto& x) {
    return ([&x]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return Hypot2<T>(x[Is]...);
    })(gslx::make_index_sequence<VectorDimension<std::decay_t<decltype(x)>>>());
}

template<std::floating_point T = double>
auto Norm(const Concept::NumericVectorIntegral auto& x) {
    return std::sqrt(Norm2<T>(x));
}

} // namespace MACE::Math
