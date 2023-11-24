#pragma once

#include "MACE/DataModel/Column/internal/ColumnSignatureBase.h++"

#include <concepts>

namespace MACE::DataModel::inline Column {

template<typename T>
concept Column = std::derived_from<T, internal::ColumnSignatureBase>;

} // namespace MACE::DataModel::inline Column
