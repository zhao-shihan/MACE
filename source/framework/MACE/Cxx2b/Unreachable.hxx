#pragma once

#include <version>

#ifdef __cpp_lib_unreachable // C++2b
    #include <utility>
#endif

namespace MACE::Cxx2b {

[[noreturn]] inline void Unreachable() {
#ifdef __cpp_lib_unreachable // C++2b
    std::unreachable();
#else // fallback: compiler extensions
    #ifdef __GNUC__
    __builtin_unreachable();
    #elif defined _MSC_VER
    __assume(false);
    #endif
#endif
}

} // namespace MACE::Cxx2b
