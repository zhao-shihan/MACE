#pragma once

#include <version>

#ifdef __cpp_lib_unreachable // C++2b
#    include <utility>
#endif

namespace MACE::inline Compatibility::std2b {

[[noreturn]] inline void unreachable() {
#ifdef __cpp_lib_unreachable
    std::unreachable(); // C++2b
#elif defined __GNUC__ or defined __clang__
    __builtin_unreachable();
#elif defined _MSC_VER
    __assume(false);
#else
    return;
#endif
}

} // namespace MACE::inline Compatibility::std2b
