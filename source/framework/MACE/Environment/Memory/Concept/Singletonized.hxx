#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Environment::Memory {

namespace internal {

class MuteSingletonBase;

} // namespace internal

template<class ADerived>
class Singleton;

namespace Concept {

template<class T>
concept Singletonized = requires {
    { T::Instance() } -> std::same_as<T&>;
    requires std::derived_from<T, Singleton<T>>;
    requires not std::is_base_of_v<internal::MuteSingletonBase, T>;
    requires Utility::Concept::NonMoveable<T>;
    requires std::is_final_v<T>;
    requires not std::is_default_constructible_v<T>; // try to constrain to private or protected constructor
};

} // namespace Concept

} // namespace MACE::Environment::Memory
