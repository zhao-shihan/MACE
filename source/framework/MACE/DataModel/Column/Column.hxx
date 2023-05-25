#pragma once

#include "MACE/DataModel/Column/internal/ColumnSignatureBase.hxx"

#include <concepts>

namespace MACE::DataModel::inline Column {

template<class T>
concept Column = std::derived_from<T, internal::ColumnSignatureBase>;

} // namespace MACE::DataModel::inline Column
