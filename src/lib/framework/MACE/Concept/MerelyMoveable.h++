#pragma once

#include "MACE/Concept/NonCopyable.h++"

#include <concepts>

namespace MACE::Concept {

/// @brief Merely moveable and not copyable
template<typename T>
concept MerelyMoveable =
    requires {
        requires NonCopyable<T>;
        requires std::movable<T>;
    };

} // namespace MACE::Concept
