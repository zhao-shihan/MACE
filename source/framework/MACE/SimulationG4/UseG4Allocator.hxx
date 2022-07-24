#pragma once

#include "MACE/SimulationG4/SingletonG4Allocator.hxx"

namespace MACE::SimulationG4 {

template<class Derived>
class UseG4Allocator {
protected:
    ~UseG4Allocator() = default;

public:
    void* operator new(std::size_t) { return static_cast<void*>(New()); }
    void* operator new(std::size_t, std::align_val_t) { return static_cast<void*>(New()); }
    void* operator new[](std::size_t) = delete;
    void* operator new[](std::size_t, std::align_val_t) = delete;

    void operator delete(void* ptr) { Delete(static_cast<Derived*>(ptr)); }
    void operator delete(void* ptr, std::align_val_t) { Delete(static_cast<Derived*>(ptr)); }
    void operator delete(void* ptr, std::size_t) { Delete(static_cast<Derived*>(ptr)); }
    void operator delete(void* ptr, std::size_t, std::align_val_t) { Delete(static_cast<Derived*>(ptr)); }
    void operator delete[](void*) = delete;
    void operator delete[](void*, std::align_val_t) = delete;
    void operator delete[](void*, std::size_t) = delete;
    void operator delete[](void*, std::size_t, std::align_val_t) = delete;

private:
    static auto New() { return SingletonG4Allocator<Derived>::Instance().MallocSingle(); }
    static void Delete(Derived* ptr) { SingletonG4Allocator<Derived>::Instance().FreeSingle(ptr); }
};

} // namespace MACE::SimulationG4
