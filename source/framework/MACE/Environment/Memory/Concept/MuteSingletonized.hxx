#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Environment::Memory {

namespace Internal {

class ISingletonBase;
class MuteSingletonBase;

} // namespace Internal

template<class ADerived>
class MuteSingleton;

namespace Concept {

template<class T>
concept IndirectlyMuteSingletonized = requires {
    requires std::is_base_of_v<Internal::MuteSingletonBase, T>;
    requires not std::is_base_of_v<Internal::ISingletonBase, T>;
    requires Utility::Concept::NonMoveable<T>;
};

template<class T>
concept MuteSingletonized = requires {
    requires std::derived_from<T, MuteSingleton<T>>;
    requires IndirectlyMuteSingletonized<T>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
