#pragma once

#include "MACE/Concept/MathVector.hxx"

#include <type_traits>

namespace MACE::Concept {

template<class T>
concept GeneralArithmetic =
    std::is_arithmetic_v<T> or
    MathVectorAny<T>;

} // namespace MACE::Concept
