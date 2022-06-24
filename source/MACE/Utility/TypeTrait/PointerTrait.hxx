#pragma once

#include "MACE/Utility/Concept/Pointer.hxx"

#include <type_traits>

namespace MACE::Utility::TypeTrait {

template<Concept::Dereferenceable T>
struct ReferencedTypeImpl {
    using Type = std::remove_reference_t<decltype(*std::declval<T>())>;
};
template<Concept::Dereferenceable T>
using ReferencedType = typename ReferencedTypeImpl<T>::Type;

} // namespace MACE::Utility::TypeTrait
