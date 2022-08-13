#pragma once

#include <tuple>
#include <utility>

namespace MACE::Utility {

/// @brief Traverses a tuple (e.g. std::tuple, std::pair, std::array, etc.).
/// The "tuple" can be anything acceptable by std::apply.
/// The usage is similar to std::ranges::for_each, except that a tuple is passed in.
template<class ATuple, class AFunctor>
constexpr void TupleForEach(ATuple&& tuple, AFunctor&& func) {
    std::apply(
        [&func]<typename... Args>(Args&&... args) {
            (func(std::forward<Args>(args)), ...);
        },
        std::forward<ATuple>(tuple));
}

} // namespace MACE::Utility
