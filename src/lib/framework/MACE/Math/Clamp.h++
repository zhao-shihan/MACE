#pragma once

#include "MACE/Utility/CETAString.h++"

#include <cassert>
#include <cmath>
#include <concepts>

namespace MACE::Math {

template<CETAString<3> AMode, std::floating_point T1, std::floating_point T2, std::floating_point T3>
    requires(AMode == "[]" or
             AMode == "[)" or
             AMode == "(]" or
             AMode == "()")
constexpr auto Clamp(T1 value, T2 low, T3 high) -> std::common_type_t<T1, T2, T3> {
    const std::common_type_t<T1, T2, T3> v{value};
    const std::common_type_t<T1, T2, T3> lo{low};
    const std::common_type_t<T1, T2, T3> hi{high};
    assert(lo < hi);
    if constexpr (AMode == "[]") {
        return v < lo ? lo :
               hi < v ? hi :
                        v;
    } else if constexpr (AMode == "[)") {
        return v < lo  ? lo :
               hi <= v ? std::nexttoward(hi, lo) :
                         v;
    } else if constexpr (AMode == "(]") {
        return v <= lo ? std::nexttoward(lo, hi) :
               hi < v  ? hi :
                         v;
    } else if constexpr (AMode == "()") {
        return v <= lo ? std::nexttoward(lo, hi) :
               hi <= v ? std::nexttoward(hi, lo) :
                         v;
    }
}

} // namespace MACE::Math
