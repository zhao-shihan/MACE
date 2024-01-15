#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Concept/GeneralArithmetic.h++"

#include <concepts>
#include <numeric>
#include <type_traits>

namespace MACE::Math {

constexpr auto MidPoint(const Concept::GeneralArithmetic auto& a,
                        const Concept::GeneralArithmetic auto& b) -> decltype(auto)
    requires(not std::same_as<decltype(a), bool> and
             not std::same_as<decltype(b), bool>) and
            requires { a + b; } and
            requires { b + a; }
{
    return (a + b) / 2;
}

constexpr auto MidPointSafe(const Concept::Arithmetic auto a,
                            const Concept::Arithmetic auto b)
    requires(not std::same_as<decltype(a), bool> and
             not std::same_as<decltype(b), bool>)
{
    return std::midpoint<std::common_type_t<decltype(a), decltype(b)>>(a, b);
}

} // namespace MACE::Math
