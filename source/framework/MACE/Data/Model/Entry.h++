#pragma once

#include "MACE/Data/Model/internal/EntryNoRecursion.h++"
#include "MACE/Data/Model/internal/ModelizedNoRecursion.h++"

namespace MACE::Data::inline Model {

template<typename E>
concept Entry =
    internal::EntryNoRecursion<E> and
    internal::ModelizedNoRecursion<typename E::Model>;

} // namespace MACE::Data::inline Model
