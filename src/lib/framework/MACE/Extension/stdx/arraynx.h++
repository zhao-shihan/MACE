#pragma once

#include <array>
#include <complex>
#include <cstddef>

namespace MACE::inline Extension::stdx {

template<typename T>
using array2 = std::array<T, 2>;
template<typename T>
using array3 = std::array<T, 3>;
template<typename T>
using array4 = std::array<T, 4>;

template<std::size_t N>
using arrayi = std::array<int, N>;
template<std::size_t N>
using arrayl = std::array<long, N>;
template<std::size_t N>
using arrayll = std::array<long long, N>;
template<std::size_t N>
using arrayu = std::array<unsigned, N>;
template<std::size_t N>
using arrayul = std::array<unsigned long, N>;
template<std::size_t N>
using arrayull = std::array<unsigned long long, N>;
template<std::size_t N>
using arrayf = std::array<float, N>;
template<std::size_t N>
using arrayd = std::array<double, N>;
template<std::size_t N>
using arrayld = std::array<long double, N>;
template<std::size_t N>
using arraycf = std::array<std::complex<float>, N>;
template<std::size_t N>
using arraycd = std::array<std::complex<double>, N>;
template<std::size_t N>
using arraycld = std::array<std::complex<long double>, N>;

using array2i = arrayi<2>;
using array2l = arrayl<2>;
using array2ll = arrayll<2>;
using array2u = arrayu<2>;
using array2ul = arrayul<2>;
using array2ull = arrayull<2>;
using array2f = arrayf<2>;
using array2d = arrayd<2>;
using array2ld = arrayld<2>;
using array2cf = arraycf<2>;
using array2cd = arraycd<2>;
using array2cld = arraycld<2>;

using array3i = arrayi<3>;
using array3l = arrayl<3>;
using array3ll = arrayll<3>;
using array3u = arrayu<3>;
using array3ul = arrayul<3>;
using array3ull = arrayull<3>;
using array3f = arrayf<3>;
using array3d = arrayd<3>;
using array3ld = arrayld<3>;
using array3cf = arraycf<3>;
using array3cd = arraycd<3>;
using array3cld = arraycld<3>;

using array4i = arrayi<4>;
using array4l = arrayl<4>;
using array4ll = arrayll<4>;
using array4u = arrayu<4>;
using array4ul = arrayul<4>;
using array4ull = arrayull<4>;
using array4f = arrayf<4>;
using array4d = arrayd<4>;
using array4ld = arrayld<4>;
using array4cf = arraycf<4>;
using array4cd = arraycd<4>;
using array4cld = arraycld<4>;

} // namespace MACE::inline Extension::stdx
