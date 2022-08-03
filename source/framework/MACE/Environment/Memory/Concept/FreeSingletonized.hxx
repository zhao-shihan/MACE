#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::Environment::Memory {

namespace Detail {

class FreeSingletonBase;
class ISingletonBase;

} // namespace Detail

template<class ADerived>
class FreeSingleton;

namespace Concept {

template<class T>
concept IndirectlyFreeSingletonized = requires {
    { T::Instance() } -> std::same_as<T&>;
    requires std::derived_from<T, Detail::FreeSingletonBase>;
    requires not std::is_base_of_v<Detail::ISingletonBase, T>;
    requires Utility::Concept::NonMoveable<T>;
};

template<class T>
concept FreeSingletonized = requires {
    requires std::derived_from<T, FreeSingleton<T>>;
    requires IndirectlyFreeSingletonized<T>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
