#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Utility {

auto ToSigned(std::integral auto k) noexcept {
    return static_cast<std::make_signed_t<decltype(k)>>(k);
}

} // namespace MACE::Utility
