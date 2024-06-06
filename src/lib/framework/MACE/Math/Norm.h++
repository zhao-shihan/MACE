#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Extension/gslx/index_sequence.h++"
#include "MACE/Utility/VectorCast.h++"
#include "MACE/Utility/VectorDimension.h++"
#include "MACE/Utility/VectorValueType.h++"

#include "muc/math"
#include "muc/utility"

#include "gsl/gsl"

#include <cmath>
#include <concepts>
#include <type_traits>

namespace MACE::Math {

constexpr auto Norm2(const Concept::NumericVectorFloatingPoint auto& x) {
    return ([&x]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return muc::hypot2(x[Is]...);
    })(gslx::make_index_sequence<VectorDimension<std::decay_t<decltype(x)>>>());
}

auto Norm(const Concept::NumericVectorFloatingPoint auto& x) {
    return std::sqrt(Norm2(x));
}

template<std::floating_point T = double>
constexpr auto Norm2(const Concept::NumericVectorIntegral auto& x) {
    return ([&x]<gsl::index... Is>(gslx::index_sequence<Is...>) {
        return muc::hypot2<T>(x[Is]...);
    })(gslx::make_index_sequence<VectorDimension<std::decay_t<decltype(x)>>>());
}

template<std::floating_point T = double>
auto Norm(const Concept::NumericVectorIntegral auto& x) {
    return std::sqrt(Norm2<T>(x));
}

} // namespace MACE::Math
