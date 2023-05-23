#pragma once

#include "MACE/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Env::Memory {

namespace internal {

class SingletonBase;
class WeakSingletonBase;

} // namespace internal

template<class ADerived>
class WeakSingleton;

template<class T>
concept IndirectlyWeakSingletonified =
    requires {
        requires std::is_base_of_v<internal::WeakSingletonBase, T>;
        requires not std::is_base_of_v<internal::SingletonBase, T>;
        requires Concept::NonMoveable<T>;
    };

template<class T>
concept WeakSingletonified =
    requires {
        requires std::derived_from<T, WeakSingleton<T>>;
        requires IndirectlyWeakSingletonified<T>;
    };

} // namespace MACE::Env::Memory
