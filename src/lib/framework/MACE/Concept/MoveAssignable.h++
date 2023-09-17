#pragma once

#include <concepts>

namespace MACE::Concept {

/// @brief C++ named requirements: MoveAssignable.
/// See also: https://en.cppreference.com/w/cpp/named_req/MoveAssignable
template<typename T>
concept MoveAssignable =
    requires(T& t, T&& rv) {
        { t = rv } -> std::same_as<T&>;
    };

template<typename T>
concept NoExceptMoveAssignable =
    requires(T& t, T&& rv) {
        { t = rv } noexcept -> std::same_as<T&>;
    };

} // namespace MACE::Concept
