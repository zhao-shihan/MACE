#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::FreeSingleton.
/// Not API. Just a signature of free singleton.
class FreeSingletonBase : public Utility::NonMoveableBase {
protected:
    FreeSingletonBase() = default;
    ~FreeSingletonBase() = default;
};

} // namespace MACE::Env::Memory::internal
