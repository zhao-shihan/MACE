#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

#include <memory>

namespace MACE::Env {

namespace Memory::internal {

class WeakSingletonPool;
class SingletonDeleter;
class SingletonPool;

} // namespace Memory::internal

namespace internal {

class EnvBase : public NonMoveableBase {
protected:
    EnvBase();
    ~EnvBase();

private:
    std::unique_ptr<Memory::internal::WeakSingletonPool> fWeakSingletonPool;
    std::unique_ptr<Memory::internal::SingletonPool> fSingletonPool;
    std::unique_ptr<Memory::internal::SingletonDeleter> fSingletonDeleter;
};

} // namespace internal

} // namespace MACE::Env
