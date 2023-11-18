#pragma once

#include <concepts>

namespace MACE::inline Extension::stdx {

template<typename B>
concept boolean_testable =
    requires(B&& b) {
        requires std::convertible_to<B, bool>;
        { not std::forward<B>(b) } -> std::convertible_to<bool>;
    };

} // namespace MACE::inline Extension::stdx
