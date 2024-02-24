#pragma once

#include <climits>
#include <cstddef>

namespace MACE::inline Utility {

template<typename T>
constexpr inline std::size_t BitWidthOf{CHAR_BIT * sizeof(T)};

} // namespace MACE::inline Utility
