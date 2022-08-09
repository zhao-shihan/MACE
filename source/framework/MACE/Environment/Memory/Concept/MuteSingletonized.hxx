#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Environment::Memory {

namespace Detail {

class ISingletonBase;
class MuteSingletonBase;

} // namespace Detail

template<class ADerived>
class MuteSingleton;

namespace Concept {

template<class T>
concept IndirectlyMuteSingletonized = requires {
    requires std::is_base_of_v<Detail::MuteSingletonBase, T>;
    requires not std::is_base_of_v<Detail::ISingletonBase, T>;
    requires Utility::Concept::NonMoveable<T>;
};

template<class T>
concept MuteSingletonized = requires {
    requires std::derived_from<T, MuteSingleton<T>>;
    requires IndirectlyMuteSingletonized<T>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
