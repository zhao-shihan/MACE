#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include <memory>

namespace MACE::Environment {

namespace Memory::Internal {

class MuteSingletonPool;
class SingletonDeleter;
class SingletonFactory;
class SingletonPool;

} // namespace Memory::Internal

namespace Internal {

class EnvironmentBase : public Utility::NonMoveableBase {
protected:
    EnvironmentBase();
    ~EnvironmentBase();

private:
    std::unique_ptr<Memory::Internal::MuteSingletonPool> fMuteSingletonPool;
    std::unique_ptr<Memory::Internal::SingletonPool> fSingletonPool;
    std::unique_ptr<Memory::Internal::SingletonFactory> fSingletonFactory;
    std::unique_ptr<Memory::Internal::SingletonDeleter> fSingletonDeleter;
};

} // namespace Internal

} // namespace MACE::Environment
