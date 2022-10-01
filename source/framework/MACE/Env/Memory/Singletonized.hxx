#pragma once

#include "MACE/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Env::Memory {

namespace internal {

class MuteSingletonBase;

} // namespace internal

template<class ADerived>
class Singleton;

template<class T>
concept Singletonized = requires {
    { T::Instance() } -> std::same_as<T&>;
    requires std::derived_from<T, Singleton<T>>;
    requires not std::is_base_of_v<internal::MuteSingletonBase, T>;
    requires Concept::NonMoveable<T>;
    requires std::is_final_v<T>;
    requires not std::is_default_constructible_v<T>; // try to constrain to private or protected constructor
};

} // namespace MACE::Env::Memory
