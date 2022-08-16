#pragma once

#include "Eigen/Core"

namespace MACE::Compatibility::Eigen34 {

// Eigen before 3.4 does not have these following useful template aliases:

template<typename T>
using Array2 = Eigen::Array<T, 2, 1>;
template<typename T>
using Array22 = Eigen::Array<T, 2, 2>;
template<typename T>
using Array2X = Eigen::Array<T, 2, Eigen::Dynamic>;
template<typename T>
using Array3 = Eigen::Array<T, 3, 1>;
template<typename T>
using Array33 = Eigen::Array<T, 3, 3>;
template<typename T>
using Array3X = Eigen::Array<T, 3, Eigen::Dynamic>;
template<typename T>
using Array4 = Eigen::Array<T, 4, 1>;
template<typename T>
using Array44 = Eigen::Array<T, 4, 4>;
template<typename T>
using Array4X = Eigen::Array<T, 4, Eigen::Dynamic>;
template<typename T>
using ArrayX = Eigen::Array<T, Eigen::Dynamic, 1>;
template<typename T>
using ArrayX2 = Eigen::Array<T, Eigen::Dynamic, 2>;
template<typename T>
using ArrayX3 = Eigen::Array<T, Eigen::Dynamic, 3>;
template<typename T>
using ArrayX4 = Eigen::Array<T, Eigen::Dynamic, 4>;
template<typename T>
using ArrayXX = Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic>;

template<typename T>
using Matrix2 = Eigen::Matrix<T, 2, 2>;
template<typename T>
using Matrix2X = Eigen::Matrix<T, 2, Eigen::Dynamic>;
template<typename T>
using Matrix3 = Eigen::Matrix<T, 3, 3>;
template<typename T>
using Matrix3X = Eigen::Matrix<T, 3, Eigen::Dynamic>;
template<typename T>
using Matrix4 = Eigen::Matrix<T, 4, 4>;
template<typename T>
using Matrix4X = Eigen::Matrix<T, 4, Eigen::Dynamic>;
template<typename T>
using MatrixX = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
template<typename T>
using MatrixX2 = Eigen::Matrix<T, Eigen::Dynamic, 2>;
template<typename T>
using MatrixX3 = Eigen::Matrix<T, Eigen::Dynamic, 3>;
template<typename T>
using MatrixX4 = Eigen::Matrix<T, Eigen::Dynamic, 4>;
template<typename T, int Size>
using RowVector = Eigen::Matrix<T, 1, Size>;
template<typename T>
using RowVector2 = Eigen::Matrix<T, 1, 2>;
template<typename T>
using RowVector3 = Eigen::Matrix<T, 1, 3>;
template<typename T>
using RowVector4 = Eigen::Matrix<T, 1, 4>;
template<typename T>
using RowVectorX = Eigen::Matrix<T, 1, Eigen::Dynamic>;
template<typename T, int Size>
using Vector = Eigen::Matrix<T, Size, 1>;
template<typename T>
using Vector2 = Eigen::Matrix<T, 2, 1>;
template<typename T>
using Vector3 = Eigen::Matrix<T, 3, 1>;
template<typename T>
using Vector4 = Eigen::Matrix<T, 4, 1>;
template<typename T>
using VectorX = Eigen::Matrix<T, Eigen::Dynamic, 1>;

} // namespace MACE::Compatibility::Eigen34
