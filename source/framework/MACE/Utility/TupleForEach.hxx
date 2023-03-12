#pragma once

#include <tuple>
#include <utility>

namespace MACE::inline Utility {

/// @brief Traverses a tuple (e.g. std::tuple, std::pair, std::array, etc.).
/// The "tuple" can be anything acceptable by std::apply.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
constexpr void TupleForEach(auto&& tuple, auto&& func) {
    std::apply(
        [&func](auto&&... args) {
            (..., func(std::forward<decltype(args)>(args)));
        },
        std::forward<decltype(tuple)>(tuple));
}

} // namespace MACE::inline Utility
