#pragma once

#include "MACE/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Env::Memory {

namespace internal {

class ISingletonBase;

} // namespace internal

template<class ADerived>
class FreeSingleton;

template<class T>
concept FreeSingletonized = requires {
    { T::Instance() } -> std::same_as<T&>;
    requires std::derived_from<T, FreeSingleton<T>>;
    requires not std::is_base_of_v<internal::ISingletonBase, T>;
    requires Concept::NonMoveable<T>;
};

} // namespace MACE::Env::Memory
