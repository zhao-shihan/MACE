#pragma once

namespace MACE::inline Utility {

// mainly for class member holding pointer reference to an exist object which is not owned by the class.
// or, as the type of pointer owned by std::unique_ptr.
template<typename T>
using ObserverPtr = T*;

} // namespace MACE::inline Utility
