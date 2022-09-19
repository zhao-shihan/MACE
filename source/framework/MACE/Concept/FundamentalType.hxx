#pragma once

#include "MACE/Concept/internal/IsPointer.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept Arithmetic =
    std::is_arithmetic_v<T>;

template<typename T>
concept Character =
    std::same_as<T, char> or
    std::same_as<T, char8_t> or
    std::same_as<T, char16_t> or
    std::same_as<T, char32_t> or
    std::same_as<T, wchar_t>;

template<typename T>
concept ArithmeticExcludeBool =
    Arithmetic<T> and
    not std::same_as<T, bool>;

template<typename T>
concept ArithmeticExcludeChar =
    Arithmetic<T> and
    not Character<T>;

template<typename T>
concept ArithmeticExcludeBoolChar =
    Arithmetic<T> and
    not std::same_as<T, bool> and
    not Character<T>;

} // namespace MACE::Concept
