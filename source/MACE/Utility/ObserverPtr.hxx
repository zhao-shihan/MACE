#pragma once

#include <type_traits>

namespace MACE::Utility {

/// Represents non-owning pointer semantic.
#ifdef _MSC_VER
template<typename T, typename...>
#else
template<typename T>
#endif
using ObserverPtr = std::add_pointer_t<T>;

} // namespace MACE::Utility
