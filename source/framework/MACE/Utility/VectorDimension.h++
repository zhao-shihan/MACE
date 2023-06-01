#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Utility/VectorValueType.h++"

namespace MACE::inline Utility {

template<Concept::NumericVectorAny T>
constexpr auto VectorDimension = sizeof(T) / sizeof(VectorValueType<T>);

} // namespace MACE::inline Utility
