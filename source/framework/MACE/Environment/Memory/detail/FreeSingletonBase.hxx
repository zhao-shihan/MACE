#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"

namespace MACE::Environment::Memory::Detail {

/// @brief Implementation detail of MACE::Environment::Memory::FreeSingleton.
/// Not API. Just a signature of free singleton.
class FreeSingletonBase : public Utility::NonCopyableBase {
protected:
    FreeSingletonBase() = default;
    ~FreeSingletonBase() = default;
};

} // namespace MACE::Environment::Memory::Detail
