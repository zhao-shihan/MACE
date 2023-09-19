#pragma once

#include "MACE/Math/QinAlgorithm.h++"
#include "MACE/Utility/InlineMacro.h++"

#include <bit>
#include <climits>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <numbers>

namespace MACE::Math::Random::inline Distribution::internal {

template<std::floating_point T>
MACE_ALWAYS_INLINE constexpr auto FastLogForCompact01(T x) {
    if constexpr (std::numeric_limits<T>::is_iec559) {
        using B =
            std::conditional_t<
                std::same_as<T, float>, std::uint32_t,
                std::conditional_t<
                    std::same_as<T, double>, std::uint64_t,
                    void>>;
        constexpr int n = std::numeric_limits<T>::digits - 1;
        constexpr int k = CHAR_BIT * sizeof(T) - 1 - n;
        const auto xBits = std::bit_cast<B>(x);
        std2b::assume(xBits > 0);
        std2b::assume(xBits < ~(~static_cast<B>(0) >> 1));
        x = std::bit_cast<T>((xBits | ~static_cast<B>(0) << n) << 2 >> 2);
        const auto r = QinRational({1.00000000000000000000000000000000000L,
                                    0.583383967700472856709787286973478877L},
                                   {0.382629200453083135302003393260680748L,
                                    1.03060337901870614323216255936183184L,
                                    0.170537349167416694276401758784217301L},
                                   x);
        return (x * r - r) +
               (static_cast<int>(xBits >> n) - ((1 << (k - 1)) - 1)) * std::numbers::ln2_v<T>;
    } else {
        return std::log(x);
    }
}

} // namespace MACE::Math::Random::inline Distribution::internal
