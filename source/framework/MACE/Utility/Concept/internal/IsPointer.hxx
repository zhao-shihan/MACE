#pragma once

#include <type_traits>

namespace MACE::Utility::Concept {

template<typename T>
concept IsPointer =
    std::is_pointer_v<T>;

} // namespace MACE::Utility::Concept
