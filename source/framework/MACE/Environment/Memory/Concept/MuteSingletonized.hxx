#pragma once

#include "MACE/Utility/Concept/NonMoveable.hxx"

#include <type_traits>

namespace MACE::Environment::Memory {

namespace Detail {

class ISingletonBase;
class MuteSingletonBase;

} // namespace Detail

template<class ADerived>
class MuteSingleton;

namespace Concept {

template<class AMuteSingleton>
concept MuteSingletonized = requires {
    requires std::is_base_of_v<MuteSingleton<AMuteSingleton>, AMuteSingleton>;
    requires not std::is_base_of_v<Detail::ISingletonBase, AMuteSingleton>;
    requires Utility::Concept::NonMoveable<AMuteSingleton>;
};

template<class AMuteSingleton>
concept WeaklyMuteSingletonized = requires {
    requires std::is_base_of_v<Detail::MuteSingletonBase, AMuteSingleton>;
    requires not std::is_base_of_v<Detail::ISingletonBase, AMuteSingleton>;
    requires Utility::Concept::NonMoveable<AMuteSingleton>;
};

} // namespace Concept

} // namespace MACE::Environment::Memory
