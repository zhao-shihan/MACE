#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

namespace MACE::Env::Memory::internal {

/// @brief Implementation detail of MACE::Env::Memory::WeakSingleton.
/// Not API. Just a signature of mute singleton.
class WeakSingletonBase : public NonMoveableBase {
protected:
    WeakSingletonBase() = default;
    ~WeakSingletonBase() = default;
};

} // namespace MACE::Env::Memory::internal
