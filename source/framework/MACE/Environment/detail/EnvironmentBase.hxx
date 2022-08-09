#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include <memory>

namespace MACE::Environment {

namespace Memory::Detail {

class MuteSingletonPool;
class SingletonDeleter;
class SingletonFactory;
class SingletonPool;

} // namespace Memory::Detail

namespace Detail {

class EnvironmentBase : public Utility::NonMoveableBase {
protected:
    EnvironmentBase();
    ~EnvironmentBase();

private:
    std::unique_ptr<Memory::Detail::MuteSingletonPool> fMuteSingletonPool;
    std::unique_ptr<Memory::Detail::SingletonPool> fSingletonPool;
    std::unique_ptr<Memory::Detail::SingletonFactory> fSingletonFactory;
    std::unique_ptr<Memory::Detail::SingletonDeleter> fSingletonDeleter;
};

} // namespace Detail

} // namespace MACE::Environment
