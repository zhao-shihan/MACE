#pragma once

#include "MACE/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Environment::Memory {

namespace internal {

class ISingletonBase;
class MuteSingletonBase;

} // namespace internal

template<class ADerived>
class MuteSingleton;

namespace Concept {

template<class T>
concept IndirectlyMuteSingletonized = requires {
    requires std::is_base_of_v<internal::MuteSingletonBase, T>;
    requires not std::is_base_of_v<internal::ISingletonBase, T>;
    requires MACE::Concept::NonMoveable<T>;
};

template<class T>
concept MuteSingletonized = requires {
    requires std::derived_from<T, MuteSingleton<T>>;
    requires IndirectlyMuteSingletonized<T>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
