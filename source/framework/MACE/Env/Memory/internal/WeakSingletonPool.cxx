#include "MACE/Env/Memory/internal/WeakSingletonPool.hxx"

#include <iostream>
#include <utility>

namespace MACE::Env::Memory::internal {

WeakSingletonPool* WeakSingletonPool::fgInstance = nullptr;

WeakSingletonPool::WeakSingletonPool() :
    NonMoveableBase(),
    fInstanceMap() {
    if (fgInstance == nullptr) {
        fgInstance = this;
    } else {
        throw std::logic_error(
            "MACE::Env::Memory::internal::WeakSingletonPool::WeakSingletonPool(): "
            "Trying to instantiate the pool twice");
    }
}

WeakSingletonPool::~WeakSingletonPool() {
    for (auto&& [type, instance] : std::as_const(fInstanceMap)) {
        if (instance != nullptr) [[unlikely]] {
            std::cerr << "MACE::Env::Memory::internal::WeakSingletonPool::~WeakSingletonPool(): "
                         "Instance of type "
                      << type.name() << " (weak singleton in environment) still survives, "
                                        "implies memory leak or following undefined behavior"
                      << std::endl;
        }
    }
    fgInstance = nullptr;
}

WeakSingletonPool& WeakSingletonPool::Instance() {
    if (fgInstance != nullptr) {
        return *fgInstance;
    } else {
        throw std::logic_error(
            "MACE::Env::Memory::internal::WeakSingletonPool::Instance(): "
            "The pool has not been instantiated or has been destructed "
            "(Maybe you forgot to instantiate an environment?)");
    }
}

} // namespace MACE::Env::Memory::internal
