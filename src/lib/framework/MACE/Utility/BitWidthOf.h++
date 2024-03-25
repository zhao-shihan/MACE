#pragma once

#include <climits>
#include <cstddef>

namespace MACE::inline Utility {

template<typename T>
constexpr auto BitWidthOf() -> std::size_t {
    return CHAR_BIT * sizeof(T);
};

} // namespace MACE::inline Utility
