#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

namespace MACE::Environment::Memory::Internal {

/// @brief Implementation detail of MACE::Environment::Memory::FreeSingleton.
/// Not API. Just a signature of free singleton.
class FreeSingletonBase : public Utility::NonMoveableBase {
protected:
    FreeSingletonBase() = default;
    ~FreeSingletonBase() = default;
};

} // namespace MACE::Environment::Memory::Detail
