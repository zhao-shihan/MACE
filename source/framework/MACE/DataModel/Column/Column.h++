#pragma once

#include "MACE/DataModel/Field/internal/FieldSignatureBase.h++"

#include <concepts>

namespace MACE::DataModel::inline Field {

template<class T>
concept Field = std::derived_from<T, internal::FieldSignatureBase>;

} // namespace MACE::DataModel::inline Field
