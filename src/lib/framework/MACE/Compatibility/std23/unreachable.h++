#pragma once

#include "MACE/Utility/InlineMacro.h++"

#include <version>

#ifdef __cpp_lib_unreachable // C++23
#    include <utility>
#endif

namespace MACE::inline Compatibility::std23 {

[[noreturn]] MACE_ALWAYS_INLINE auto unreachable() -> void {
#ifdef __cpp_lib_unreachable
    std::unreachable(); // C++23
#elif defined __clang__ or defined __GNUC__
    __builtin_unreachable();
#elif defined _MSC_VER
    __assume(false);
#endif
}

} // namespace MACE::inline Compatibility::std23
