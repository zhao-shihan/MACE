#pragma once

#include <type_traits>

namespace MACE::Environment::Memory {

template<class ADerived>
class FreeSingleton;

namespace Concept {

template<class AFreeSingleton>
concept FreeSingletonized = requires {
    requires std::is_base_of_v<FreeSingleton<AFreeSingleton>, AFreeSingleton>;
    requires not std::is_constructible_v<AFreeSingleton, const AFreeSingleton&>;
    requires not std::is_convertible_v<const AFreeSingleton&, AFreeSingleton>;
    requires not std::is_constructible_v<AFreeSingleton, AFreeSingleton&>;
    requires not std::is_convertible_v<AFreeSingleton&, AFreeSingleton>;
    requires not std::is_constructible_v<AFreeSingleton, const AFreeSingleton>;
    requires not std::is_convertible_v<const AFreeSingleton, AFreeSingleton>;
    requires not std::is_constructible_v<AFreeSingleton, AFreeSingleton>;
    requires not std::is_convertible_v<AFreeSingleton, AFreeSingleton>;
    requires not std::is_assignable_v<AFreeSingleton&, const AFreeSingleton&>;
    requires not std::is_assignable_v<AFreeSingleton&, AFreeSingleton&>;
    requires not std::is_assignable_v<AFreeSingleton&, const AFreeSingleton>;
    requires not std::is_assignable_v<AFreeSingleton&, AFreeSingleton>;
    requires not std::is_swappable_v<AFreeSingleton>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
