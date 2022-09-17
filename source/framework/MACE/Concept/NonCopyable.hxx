#pragma once

#include <type_traits>

namespace MACE::Concept {

/// @brief Not copyable but can be moveable
template<typename T>
concept NonCopyable = requires {
    requires not std::is_constructible_v<T, const T&>;
    requires not std::is_convertible_v<const T&, T>;
    requires not std::is_constructible_v<T, T&>;
    requires not std::is_convertible_v<T&, T>;
    requires not std::is_assignable_v<T&, const T&>;
    requires not std::is_assignable_v<T&, T&>;
};

} // namespace MACE::Concept
