#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <type_traits>

namespace MACE::Environment::Memory {

namespace Detail {

class MuteSingletonBase;

} // namespace Detail

template<class ADerived>
class Singleton;

namespace Concept {

template<class ASingleton>
concept Singletonized = requires {
    requires std::is_base_of_v<Singleton<ASingleton>, ASingleton>;
    requires not std::is_base_of_v<Detail::MuteSingletonBase, ASingleton>;
    requires not std::is_default_constructible_v<ASingleton>; // try to constrain to private or protected constructor
    requires Utility::Concept::NonMoveable<ASingleton>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
