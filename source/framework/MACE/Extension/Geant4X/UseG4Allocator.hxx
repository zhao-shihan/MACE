#pragma once

#include "MACE/Extension/Geant4X/SingletonG4Allocator.hxx"

#include <concepts>
#include <type_traits>

namespace MACE::inline Extension::Geant4X {

template<class ADerived>
class UseG4Allocator {
protected:
    UseG4Allocator();
    ~UseG4Allocator() = default;

public:
    [[nodiscard]] void* operator new(std::size_t);
    [[nodiscard]] void* operator new[](std::size_t) = delete;

    void operator delete(void* ptr);
    void operator delete[](void*) = delete;
};

} // namespace MACE::inline Extension::Geant4X

#include "MACE/Extension/Geant4X/UseG4Allocator.inl"
