#pragma once

#include <concepts>
#include <type_traits>

namespace MACE::Utility {

auto ToUnsigned(std::integral auto k) noexcept {
    return static_cast<std::make_unsigned_t<decltype(k)>>(k);
}

} // namespace MACE::Utility
