#pragma once

#include "MACE/Utility/InlineMacro.h++"

#include <version>

#ifdef __cpp_lib_unreachable // C++2b
#    include <utility>
#endif

namespace MACE::inline Compatibility::std2b {

[[noreturn]] MACE_ALWAYS_INLINE void unreachable() {
#ifdef __cpp_lib_unreachable
    std::unreachable(); // C++2b
#elif defined __clang__ or defined __GNUC__
    __builtin_unreachable();
#elif defined _MSC_VER
    __assume(false);
#endif
}

} // namespace MACE::inline Compatibility::std2b
