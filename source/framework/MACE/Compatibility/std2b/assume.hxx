#pragma once

#include "MACE/Utility/InlineMacro.hxx"

#if not __has_cpp_attribute(assume) and \
    not(defined __clang__ or defined __GNUC__ or defined _MSC_VER)
#    include "MACE/Compatibility/std2b/unreachable.hxx"
#endif

namespace MACE::inline Compatibility::std2b {

MACE_ALWAYS_INLINE constexpr void assume(bool condition) noexcept {
#if __has_cpp_attribute(assume)
    [[assume(condition)]]; // C++2b
#elif defined __clang__
    __builtin_assume(condition);
#elif defined __GNUC__
    if (not condition) { __builtin_unreachable(); }
#elif defined _MSC_VER
    __assume(condition);
#else
    if (not condition) { unreachable(); }
#endif
}

} // namespace MACE::inline Compatibility::std2b
