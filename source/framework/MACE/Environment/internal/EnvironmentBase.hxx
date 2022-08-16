#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include <memory>

namespace MACE::Environment {

namespace Memory::internal {

class MuteSingletonPool;
class SingletonDeleter;
class SingletonFactory;
class SingletonPool;

} // namespace Memory::internal

namespace internal {

class EnvironmentBase : public Utility::NonMoveableBase {
protected:
    EnvironmentBase();
    ~EnvironmentBase();

private:
    std::unique_ptr<Memory::internal::MuteSingletonPool> fMuteSingletonPool;
    std::unique_ptr<Memory::internal::SingletonPool> fSingletonPool;
    std::unique_ptr<Memory::internal::SingletonFactory> fSingletonFactory;
    std::unique_ptr<Memory::internal::SingletonDeleter> fSingletonDeleter;
};

} // namespace internal

} // namespace MACE::Environment
