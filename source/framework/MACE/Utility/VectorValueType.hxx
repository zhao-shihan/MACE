#pragma once

#include "MACE/Concept/InputVector.hxx"

namespace MACE::inline Utility {

template<Concept::InputVectorAny T>
using VectorValueType = std::remove_reference_t<decltype(std::declval<T&>()[std::declval<gsl::index>()])>;

} // namespace MACE::inline Utility
