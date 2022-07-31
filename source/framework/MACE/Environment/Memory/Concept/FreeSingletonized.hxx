#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <type_traits>

namespace MACE::Environment::Memory {

namespace Detail {

class FreeSingletonBase;
class ISingletonBase;

} // namespace Detail

template<class ADerived>
class FreeSingleton;

namespace Concept {

template<class AFreeSingleton>
concept FreeSingletonized = requires {
    requires std::is_base_of_v<Detail::FreeSingletonBase, AFreeSingleton>;
    requires not std::is_base_of_v<Detail::ISingletonBase, AFreeSingleton>;
    requires Utility::Concept::NonMoveable<AFreeSingleton>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
