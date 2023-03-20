#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::PassiveSingleton.
/// Not API. Just a signature of passive singleton.
class PassiveSingletonBase : public NonMoveableBase {
protected:
    PassiveSingletonBase() = default;
    ~PassiveSingletonBase() = default;
};

} // namespace MACE::Env::Memory::internal
