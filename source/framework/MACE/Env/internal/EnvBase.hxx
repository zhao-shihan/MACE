#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include <memory>

namespace MACE::Env {

namespace Memory::internal {

class MuteSingletonPool;
class SingletonDeleter;
class SingletonFactory;
class SingletonPool;

} // namespace Memory::internal

namespace internal {

class EnvBase : public NonMoveableBase {
protected:
    EnvBase();
    ~EnvBase();

private:
    std::unique_ptr<Memory::internal::MuteSingletonPool> fMuteSingletonPool;
    std::unique_ptr<Memory::internal::SingletonPool> fSingletonPool;
    std::unique_ptr<Memory::internal::SingletonFactory> fSingletonFactory;
    std::unique_ptr<Memory::internal::SingletonDeleter> fSingletonDeleter;
};

} // namespace internal

} // namespace MACE::Env
