#pragma once

#include "MACE/Extension/stdx/tuple_like.h++"

namespace MACE::inline Extension::stdx {

template<typename T>
concept pair_like =
    requires {
        requires tuple_like<T>;
        requires std::tuple_size_v<T> == 2;
    };

} // namespace MACE::inline Extension::stdx
