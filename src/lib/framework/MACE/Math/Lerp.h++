#pragma once

#include "MACE/Concept/FundamentalType.h++"
#include "MACE/Concept/MathVector.h++"
#include "MACE/Utility/VectorValueType.h++"

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
    requires(not std::same_as<VectorValueType<std::decay_t<decltype(a)>>, bool> and
             not std::same_as<VectorValueType<std::decay_t<decltype(b)>>, bool> and
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
