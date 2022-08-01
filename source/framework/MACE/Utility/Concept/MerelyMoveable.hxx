#pragma once

#include "MACE/Utility/Concept/NonCopyable.hxx"

#include <concepts>

namespace MACE::Utility::Concept {

/// @brief Merely moveable and not copyable
template<typename T>
concept MerelyMoveable = requires {
    requires NonCopyable<T>;
    requires std::movable<T>;
};

} // namespace MACE::Utility::Concept
