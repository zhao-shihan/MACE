#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Environment::Memory {

namespace internal {

class FreeSingletonBase;
class ISingletonBase;

} // namespace internal

template<class ADerived>
class FreeSingleton;

namespace Concept {

template<class T>
concept FreeSingletonized = requires {
    { T::Instance() } -> std::same_as<T&>;
    requires std::derived_from<T, FreeSingleton<T>>;
    requires not std::is_base_of_v<internal::ISingletonBase, T>;
    requires Utility::Concept::NonMoveable<T>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
