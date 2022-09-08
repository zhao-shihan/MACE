#pragma once

#include <version>

#ifdef __cpp_lib_unreachable // C++2b
#    include <utility>
#endif

namespace MACE::Compatibility::std2b {

[[noreturn]] inline void unreachable() {
#ifdef __cpp_lib_unreachable // C++2b
    std::unreachable();
#else // fallback: compiler extensions
#    ifdef __GNUC__
    __builtin_unreachable();
#    elif defined _MSC_VER
    __assume(false);
#    endif
#endif
}

} // namespace MACE::Compatibility::std2b
