#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

namespace MACE::Environment::Memory::Detail {

/// @brief Implementation detail of MACE::Environment::Memory::MuteSingleton.
/// Not API. Just a signature of mute singleton.
class MuteSingletonBase : private Utility::NonMoveableBase {
protected:
    MuteSingletonBase() = default;
    ~MuteSingletonBase() = default;
};

} // namespace MACE::Environment::Memory::Detail
