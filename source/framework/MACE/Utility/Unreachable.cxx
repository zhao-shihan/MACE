#include "MACE/Utility/Unreachable.hxx"

#include <version>

#ifdef __cpp_lib_unreachable // C++23
    #include <utility>
#endif

namespace MACE::Utility {

[[noreturn]] void Unreachable() {
#ifdef __cpp_lib_unreachable // C++23
    std::unreachable();
#else // Fallback to compiler extensions
    #ifdef __GNUC__
    __builtin_unreachable();
    #elif defined _MSC_VER
    __assume(false);
    #endif
#endif
}

} // namespace MACE::Utility
