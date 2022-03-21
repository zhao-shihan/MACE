#pragma once

#include "Eigen/src/Core/util/Macros.h"

namespace Eigen {

#if !EIGEN_VERSION_AT_LEAST(3, 4, 0)
//
// Eigen before 3.4 does not have these following useful template typedefs:
//
template<typename Type>
using Matrix2 = Matrix<Type, 2, 2>;
template<typename Type>
using Matrix2X = Matrix<Type, 2, Dynamic>;
template<typename Type>
using Matrix3 = Matrix<Type, 3, 3>;
template<typename Type>
using Matrix3X = Matrix<Type, 3, Dynamic>;
template<typename Type>
using Matrix4 = Matrix<Type, 4, 4>;
template<typename Type>
using Matrix4X = Matrix<Type, 4, Dynamic>;
template<typename Type>
using MatrixX = Matrix<Type, Dynamic, Dynamic>;
template<typename Type>
using MatrixX2 = Matrix<Type, Dynamic, 2>;
template<typename Type>
using MatrixX3 = Matrix<Type, Dynamic, 3>;
template<typename Type>
using MatrixX4 = Matrix<Type, Dynamic, 4>;
template<typename Type, int Size>
using RowVector = Matrix<Type, 1, Size>;
template<typename Type>
using RowVector2 = Matrix<Type, 1, 2>;
template<typename Type>
using RowVector3 = Matrix<Type, 1, 3>;
template<typename Type>
using RowVector4 = Matrix<Type, 1, 4>;
template<typename Type>
using RowVectorX = Matrix<Type, 1, Dynamic>;
template<typename Type, int Size>
using Vector = Matrix<Type, Size, 1>;
template<typename Type>
using Vector2 = Matrix<Type, 2, 1>;
template<typename Type>
using Vector3 = Matrix<Type, 3, 1>;
template<typename Type>
using Vector4 = Matrix<Type, 4, 1>;
template<typename Type>
using VectorX = Matrix<Type, Dynamic, 1>;
#endif

} // namespace Eigen
