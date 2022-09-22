#pragma once

#include "MACE/Concept/MoveAssignable.hxx"

#include <concepts>

namespace MACE::Concept {

/// @brief C++ named requirements: CopyAssignable.
/// See also: https://en.cppreference.com/w/cpp/named_req/CopyAssignable
template<typename T>
concept CopyAssignable = requires(T& t, T& lv, const T& clv, const T&& crv) {
    requires Concept::MoveAssignable<T>;
    { t = lv } -> std::same_as<T&>;
    { t = clv } -> std::same_as<T&>;
    { t = crv } -> std::same_as<T&>;
};

template<typename T>
concept NoExceptCopyAssignable = requires(T& t, T& lv, const T& clv, const T&& crv) {
    requires Concept::MoveAssignable<T>; // clang-format off
    { t = lv } noexcept -> std::same_as<T&>;
    { t = clv } noexcept -> std::same_as<T&>;
    { t = crv } noexcept -> std::same_as<T&>; // clang-format on
};

} // namespace MACE::Concept
