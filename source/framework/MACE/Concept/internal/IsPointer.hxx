#pragma once

#include <type_traits>

namespace MACE::Concept {

template<typename T>
concept IsPointer =
    std::is_pointer_v<T>;

} // namespace MACE::Concept
