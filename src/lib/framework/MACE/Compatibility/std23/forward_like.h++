#pragma once

#include "MACE/Utility/InlineMacro.h++"

#include <utility>
#include <version>

#ifndef __cpp_lib_forward_like // backport
#    include <type_traits>
#endif

namespace MACE::inline Compatibility::std23 {

template<typename T, typename U>
[[nodiscard]] MACE_ALWAYS_INLINE constexpr auto forward_like(U&& x) noexcept -> auto&& {
#ifdef __cpp_lib_forward_like // C++23
    return std::forward_like<T, U>(x);
#else // backport
    constexpr bool is_adding_const = std::is_const_v<std::remove_reference_t<T>>;
    if constexpr (std::is_lvalue_reference_v<T&&>) {
        if constexpr (is_adding_const) {
            return std::as_const(x);
        } else {
            return static_cast<U&>(x);
        }
    } else {
        if constexpr (is_adding_const) {
            return std::move(std::as_const(x));
        } else {
            return std::move(x);
        }
    }
#endif
}

} // namespace MACE::inline Compatibility::std23
