#pragma once

#include <array>

namespace MACE::inline Extension::stdx {

template<typename T>
using array2 = std::array<T, 2>;
using array2d = array2<double>;
using array2f = array2<float>;
using array2i = array2<int>;

template<typename T>
using array3 = std::array<T, 3>;
using array3d = array3<double>;
using array3f = array3<float>;
using array3i = array3<int>;

template<typename T>
using array4 = std::array<T, 4>;
using array4d = array4<double>;
using array4f = array4<float>;
using array4i = array4<int>;

} // namespace MACE::inline Extension::stdx
