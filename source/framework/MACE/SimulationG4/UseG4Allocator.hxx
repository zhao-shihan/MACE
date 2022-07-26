#pragma once

#include "MACE/SimulationG4/SingletonG4Allocator.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::SimulationG4 {

template<class ADerived>
class UseG4Allocator {
protected:
    UseG4Allocator();
    ~UseG4Allocator() = default;

public:
    void* operator new(std::size_t) { return SingletonG4Allocator<ADerived>::Instance().MallocSingle(); }
    void* operator new[](std::size_t) = delete;

    void operator delete(void* ptr) { SingletonG4Allocator<ADerived>::Instance().FreeSingle(static_cast<ADerived*>(ptr)); }
    void operator delete[](void*) = delete;
};

} // namespace MACE::SimulationG4

#include "MACE/SimulationG4/UseG4Allocator.inl"
