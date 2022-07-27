#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"

#include <memory>

namespace MACE::Environment {

namespace Memory::Detail {

class FreeSingletonPool;
class SingletonFactory;

} // namespace Memory::Detail

namespace Detail {

class EnvironmentBase : public Utility::NonCopyableBase {
protected:
    EnvironmentBase();
    ~EnvironmentBase();

private:
    std::unique_ptr<Memory::Detail::FreeSingletonPool> fFreeSingletonPool;
    std::unique_ptr<Memory::Detail::SingletonFactory> fSingletonFactory;
};

} // namespace Detail

} // namespace MACE::Environment
