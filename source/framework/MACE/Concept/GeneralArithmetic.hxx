#pragma once

#include "MACE/Concept/NumericVector.hxx"

#include <type_traits>

namespace MACE::Concept {

template<class T>
concept GeneralArithmetic =
    std::is_arithmetic_v<T> or
    NumericVectorAny<T>;

} // namespace MACE::Concept
