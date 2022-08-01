#pragma once

#include <version>

#ifdef __cpp_lib_to_underlying // C++2b
    #include <utility>
#else // fallback: manual implementation
    #include <type_traits>
#endif

namespace MACE::Cxx2b {

template<class AEnum>
constexpr std::underlying_type_t<AEnum> ToUnderlying(AEnum enumValue) noexcept {
#ifdef __cpp_lib_to_underlying // C++2b
    return std::to_underlying<AEnum>(enumValue);
#else // fallback: manual implementation
    return static_cast<typename std::underlying_type<AEnum>::type>(enumValue);
#endif
}

} // namespace MACE::Cxx2b
