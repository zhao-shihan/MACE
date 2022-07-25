#pragma once

#include "MACE/SimulationG4/SingletonG4Allocator.hxx"

namespace MACE::SimulationG4 {

template<class Derived>
class UseG4Allocator {
protected:
    ~UseG4Allocator() = default;

public:
    void* operator new(std::size_t) { return SingletonG4Allocator<Derived>::Instance().MallocSingle(); }
    void* operator new[](std::size_t) = delete;

    void operator delete(void* ptr) { SingletonG4Allocator<Derived>::Instance().FreeSingle(static_cast<Derived*>(ptr)); }
    void operator delete[](void*) = delete;
};

} // namespace MACE::SimulationG4
