#pragma once

#include "MACE/Concept/NonMoveable.h++"

#include <concepts>
#include <type_traits>

namespace MACE::Env::Memory {

namespace internal {

class SingletonBase;

} // namespace internal

template<class ADerived>
class PassiveSingleton;

template<class T>
concept PassiveSingletonified =
    requires {
        { T::Instance() } -> std::same_as<T&>;
        requires std::derived_from<T, PassiveSingleton<T>>;
        requires not std::is_base_of_v<internal::SingletonBase, T>;
        requires Concept::NonMoveable<T>;
    };

} // namespace MACE::Env::Memory
