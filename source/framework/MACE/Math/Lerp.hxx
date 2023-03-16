#pragma once

#include "MACE/Concept/FundamentalType.hxx"
#include "MACE/Concept/MathVector.hxx"
#include "MACE/Utility/ValueTypeOf.hxx"

#include <cmath>
#include <concepts>
#include <type_traits>

namespace MACE::Math {

constexpr auto Lerp(const Concept::Arithmetic auto a,
                    const Concept::Arithmetic auto b,
                    const Concept::Arithmetic auto t)
    requires(not std::same_as<decltype(a), bool> and
             not std::same_as<decltype(b), bool> and
             not std::same_as<decltype(t), bool>)
{
    return a + t * (b - a);
}

constexpr decltype(auto) Lerp(const Concept::MathVectorAny auto& a,
                              const Concept::MathVectorAny auto& b,
                              const Concept::Arithmetic auto t)
    requires(not std::same_as<ValueTypeOf<decltype(a)>, bool> and
             not std::same_as<ValueTypeOf<decltype(b)>, bool> and
             not std::same_as<decltype(t), bool>) and
            requires { b - a; } and
            requires { a - b; }
{
    return a + t * (b - a);
}

constexpr auto LerpSafe(const Concept::Arithmetic auto a,
                        const Concept::Arithmetic auto b,
                        const Concept::Arithmetic auto t)
    requires(not std::same_as<decltype(a), bool> and
             not std::same_as<decltype(b), bool> and
             not std::same_as<decltype(t), bool>)
{
    return std::lerp(a, b, t);
}

} // namespace MACE::Math
