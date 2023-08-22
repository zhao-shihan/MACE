#pragma once

#include "MACE/Data/Model/internal/DataEntryNoRecursion.h++"
#include "MACE/Data/Model/internal/DataModelNoRecursion.h++"

namespace MACE::Data::inline Model {

template<typename E>
concept DataEntry =
    internal::DataEntryNoRecursion<E> and
    internal::DataModelNoRecursion<typename E::Model>;

} // namespace MACE::Data::inline Model
