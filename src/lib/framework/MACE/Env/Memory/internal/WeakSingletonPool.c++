#include "MACE/Env/Memory/internal/WeakSingletonPool.h++"

#include <iostream>
#include <utility>

namespace MACE::Env::Memory::internal {

WeakSingletonPool* WeakSingletonPool::fgInstance = nullptr;

WeakSingletonPool::WeakSingletonPool() :
    NonMoveableBase{},
    fInstanceMap{} {
    if (fgInstance == nullptr) {
        fgInstance = this;
    } else {
        throw std::logic_error{"MACE::Env::Memory::internal::WeakSingletonPool::WeakSingletonPool(): "
                               "Trying to instantiate the pool twice"};
    }
}

WeakSingletonPool::~WeakSingletonPool() {
    for (auto&& [type, instance] : std::as_const(fInstanceMap)) {
        if (*instance != nullptr) [[unlikely]] {
            fmt::println(stderr,
                         "MACE::Env::Memory::internal::WeakSingletonPool::~WeakSingletonPool(): "
                         "Instance of type {} (weak singleton in environment) still survives, "
                         "implies memory leak or following undefined behavior",
                         type.name());
        }
    }
    fgInstance = nullptr;
}

auto WeakSingletonPool::Instance() -> WeakSingletonPool& {
    if (fgInstance != nullptr) {
        return *fgInstance;
    } else {
        throw std::logic_error{"MACE::Env::Memory::internal::WeakSingletonPool::Instance(): "
                               "The pool has not been instantiated or has been destructed "
                               "(Maybe you forgot to instantiate an environment?)"};
    }
}

} // namespace MACE::Env::Memory::internal
