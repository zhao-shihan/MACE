#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::inline Extension::stdx {

constexpr auto to_signed(std::integral auto k) -> std::make_signed_t<decltype(k)> {
    return k;
}

} // namespace MACE::inline Extension::stdx
