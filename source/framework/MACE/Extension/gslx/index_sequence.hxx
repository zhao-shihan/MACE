#pragma once

#include "gsl/gsl"

#include <utility>

namespace MACE::inline Extension::gslx {

template<gsl::index... I>
using index_sequence = std::integer_sequence<gsl::index, I...>;

template<gsl::index N>
using make_index_sequence = std::make_integer_sequence<gsl::index, N>;

template<class... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

} // namespace MACE::inline Extension::gslx
