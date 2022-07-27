#include "MACE/Environment/Memory/detail/FreeSingletonPool.hxx"

#include <iostream>
#include <utility>

namespace MACE::Environment::Memory::Detail {

ObserverPtr<FreeSingletonPool> FreeSingletonPool::fgInstance = nullptr;

FreeSingletonPool::FreeSingletonPool() :
    NonCopyableBase(),
    fInstanceMap() {
    if (fgInstance == nullptr) {
        fgInstance = this;
    } else {
        throw std::logic_error("MACE::Environment::Memory::Detail::FreeSingletonPool::FreeSingletonPool(): Trying to instantiate the pool twice");
    }
}

FreeSingletonPool::~FreeSingletonPool() {
    for (auto&& [type, instance] : std::as_const(fInstanceMap)) {
        if (instance != nullptr) [[unlikely]] {
            std::clog << "MACE::Environment::Memory::Detail::FreeSingletonPool::~FreeSingletonPool(): Instance of type " << type.name() << " (free singleton in environment) still survives, implies memory leak or following undefined behavior" << std::endl;
        }
    }
    fgInstance = nullptr;
}

FreeSingletonPool& FreeSingletonPool::Instance() {
    if (fgInstance != nullptr) {
        return *fgInstance;
    } else {
        throw std::logic_error("MACE::Environment::Memory::Detail::FreeSingletonPool::Instance(): The pool has not been instantiated or has been destructed");
    }
}

} // namespace MACE::Environment::Memory::Detail
