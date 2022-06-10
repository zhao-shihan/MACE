#pragma once

#include <type_traits>

namespace MACE::Utility::Concept {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

} // namespace MACE::Utility::Concept
