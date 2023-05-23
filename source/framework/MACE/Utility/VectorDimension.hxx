#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Utility/VectorValueType.hxx"

namespace MACE::inline Utility {

template<Concept::NumericVectorAny T>
constexpr auto VectorDimension = sizeof(T) / sizeof(VectorValueType<T>);

} // namespace MACE::inline Utility
