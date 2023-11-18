#pragma once

#include "MACE/Extension/Geant4X/SingletonG4Allocator.h++"
#include "MACE/Utility/InlineMacro.h++"

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace MACE::inline Extension::Geant4X {

template<typename ADerived>
class UseG4Allocator {
protected:
    UseG4Allocator() = default;
    ~UseG4Allocator() = default;

public:
    [[nodiscard]] MACE_ALWAYS_INLINE auto operator new(std::size_t) -> void*;
    [[nodiscard]] MACE_ALWAYS_INLINE auto operator new[](std::size_t) -> void* = delete;

    MACE_ALWAYS_INLINE auto operator delete(void* ptr) -> void;
    MACE_ALWAYS_INLINE auto operator delete[](void*) -> void = delete;
};

} // namespace MACE::inline Extension::Geant4X

#include "MACE/Extension/Geant4X/UseG4Allocator.inl"
