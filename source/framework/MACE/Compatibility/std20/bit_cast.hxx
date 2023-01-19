#pragma once

#include <version>

#ifdef __cpp_lib_bit_cast // 201806L
#    include <bit>
#else // backport
#    include <cstring>
#    include <type_traits>
#endif

namespace MACE::inline Compatibility::std20 {

#ifdef __cpp_lib_bit_cast // 201806L

template<class To, class From>
[[nodiscard]] constexpr To bit_cast(const From& from) noexcept {
    return std::bit_cast<To>(from);
}

#else // backport

/// @brief See https://en.cppreference.com/w/cpp/numeric/bit_cast. GCC 10 does
/// not implement this function, so we provide a backport.
/// @tparam To The type you want to cast to.
/// @tparam From The const-referenced type of from.
/// @param from The source of bits for the return value.
/// @return An object of type To whose value representation is as described above.
template<class To, class From>
    requires(sizeof(To) == sizeof(From) and
             std::is_trivially_copyable_v<From> and
             std::is_trivially_copyable_v<To> and
             std::is_trivially_constructible_v<To>)
[[nodiscard]] To bit_cast(const From& from) noexcept {
    To to;
    std::memcpy(&to, &from, sizeof(To));
    return to;
}

#endif

} // namespace MACE::inline Compatibility::std20
