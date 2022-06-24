#pragma once

namespace MACE::Utility {

/// Represents non-owning pointer semantic.
#ifdef _MSC_VER
template<typename T, typename...>
#else
template<typename T>
#endif
using ObserverPtr = T*;

} // namespace MACE::Utility
