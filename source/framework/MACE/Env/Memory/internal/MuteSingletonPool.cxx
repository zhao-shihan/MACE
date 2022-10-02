#include "MACE/Env/Memory/internal/MuteSingletonPool.hxx"

#include <iostream>
#include <utility>

namespace MACE::Env::Memory::internal {

MuteSingletonPool* MuteSingletonPool::fgInstance = nullptr;

MuteSingletonPool::MuteSingletonPool() :
    NonMoveableBase(),
    fInstanceMap() {
    if (fgInstance == nullptr) {
        fgInstance = this;
    } else {
        throw std::logic_error(
            "MACE::Env::Memory::internal::MuteSingletonPool::MuteSingletonPool(): "
            "Trying to instantiate the pool twice");
    }
}

MuteSingletonPool::~MuteSingletonPool() {
    for (auto&& [type, instance] : std::as_const(fInstanceMap)) {
        if (instance != nullptr) [[unlikely]] {
            std::cerr << "MACE::Env::Memory::internal::MuteSingletonPool::~MuteSingletonPool(): "
                         "Instance of type "
                      << type.name() << " (mute singleton in environment) still survives, "
                                        "implies memory leak or following undefined behavior"
                      << std::endl;
        }
    }
    fgInstance = nullptr;
}

MuteSingletonPool& MuteSingletonPool::Instance() {
    if (fgInstance != nullptr) {
        return *fgInstance;
    } else {
        throw std::logic_error(
            "MACE::Env::Memory::internal::MuteSingletonPool::Instance(): "
            "The pool has not been instantiated or has been destructed "
            "(Maybe you forgot to instantiate an environment?)");
    }
}

} // namespace MACE::Env::Memory::internal
