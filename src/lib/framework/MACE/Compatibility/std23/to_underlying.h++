#pragma once

#include <version>

#ifdef __cpp_lib_to_underlying // C++2b
#    include <utility>
#else // backport
#    include <type_traits>
#endif

namespace MACE::inline Compatibility::std23 {

template<typename AEnum>
constexpr std::underlying_type_t<AEnum> to_underlying(AEnum enumValue) noexcept {
#ifdef __cpp_lib_to_underlying // C++2b
    return std::to_underlying<AEnum>(enumValue);
#else // backport
    return static_cast<typename std::underlying_type<AEnum>::type>(enumValue);
#endif
}

} // namespace MACE::inline Compatibility::std23
