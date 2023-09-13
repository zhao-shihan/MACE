#pragma once

#include "MACE/Data/Model/internal/EntryNoRecursion.h++"
#include "MACE/Data/Model/internal/ModelizedNoRecursion.h++"

namespace MACE::Data::inline Model {

template<class M>
concept Modelized =
    internal::ModelizedNoRecursion<M> and
    internal::EntryNoRecursion<typename M::Entry>;

} // namespace MACE::Data::inline Model
