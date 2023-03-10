#pragma once

#include <cstddef>

namespace std {

template<class T, std::size_t N>
struct array;

} // namespace std

namespace MACE::stdx {

template<typename T>
using array2 = std::array<T, 2>;
using array2d = stdx::array2<double>;
using array2f = stdx::array2<float>;
using array2i = stdx::array2<int>;

template<typename T>
using array3 = std::array<T, 3>;
using array3d = stdx::array3<double>;
using array3f = stdx::array3<float>;
using array3i = stdx::array3<int>;

template<typename T>
using array4 = std::array<T, 4>;
using array4d = stdx::array4<double>;
using array4f = stdx::array4<float>;
using array4i = stdx::array4<int>;

} // namespace MACE::stdx
