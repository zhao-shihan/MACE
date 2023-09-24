#pragma once

#include <type_traits>

namespace MACE::inline Extension::stdx {

template<typename T>
struct remove_cref
    : std::remove_const<std::remove_reference_t<T>> {};

template<typename T>
using remove_cref_t = typename remove_cref<T>::type;

} // namespace MACE::inline Extension::stdx
