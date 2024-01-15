#pragma once

#include <type_traits>

namespace MACE::inline Extension::stdx {

template<typename T>
struct remove_vref
    : std::remove_volatile<std::remove_reference_t<T>> {};

template<typename T>
using remove_vref_t = typename remove_vref<T>::type;

} // namespace MACE::inline Extension::stdx
