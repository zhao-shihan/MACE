#pragma once

#include "MACE/Concept/FundamentalType.hxx"

#include <numeric>
#include <type_traits>

namespace MACE::Math {

constexpr auto MidPoint(Concept::Arithmetic auto a, Concept::Arithmetic auto b)
    requires(not std::same_as<decltype(a), bool> and not std::same_as<decltype(b), bool>)
{
    return (a + b) / 2;
}

constexpr auto MidPointSafe(Concept::Arithmetic auto a, Concept::Arithmetic auto b)
    requires(not std::same_as<decltype(a), bool> and not std::same_as<decltype(b), bool>)
{
    return std::midpoint<std::common_type_t<decltype(a), decltype(b)>>(a, b);
}

} // namespace MACE::Math
