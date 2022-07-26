#pragma once

#include <type_traits>

namespace MACE::Environment::Memory {

template<class ADerived>
class Singleton;

namespace Concept {

template<class ASingleton>
concept Singletonized = requires {
    requires std::is_base_of_v<Singleton<ASingleton>, ASingleton>;
    requires not std::is_default_constructible_v<ASingleton>; // private or protected constructor
    requires not std::is_constructible_v<ASingleton, const ASingleton&>;
    requires not std::is_convertible_v<const ASingleton&, ASingleton>;
    requires not std::is_constructible_v<ASingleton, ASingleton&>;
    requires not std::is_convertible_v<ASingleton&, ASingleton>;
    requires not std::is_constructible_v<ASingleton, const ASingleton>;
    requires not std::is_convertible_v<const ASingleton, ASingleton>;
    requires not std::is_constructible_v<ASingleton, ASingleton>;
    requires not std::is_convertible_v<ASingleton, ASingleton>;
    requires not std::is_assignable_v<ASingleton&, const ASingleton&>;
    requires not std::is_assignable_v<ASingleton&, ASingleton&>;
    requires not std::is_assignable_v<ASingleton&, const ASingleton>;
    requires not std::is_assignable_v<ASingleton&, ASingleton>;
    requires not std::is_swappable_v<ASingleton>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
