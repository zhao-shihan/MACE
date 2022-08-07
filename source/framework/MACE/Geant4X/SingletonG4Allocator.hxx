#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"

#include "G4Allocator.hh"

namespace MACE::Geant4X {

template<class T>
class SingletonG4Allocator final : public Environment::Memory::Singleton<SingletonG4Allocator<T>>,
                                   public G4Allocator<T> {
    friend Environment::Memory::SingletonFactory;

private:
    SingletonG4Allocator() = default;
    ~SingletonG4Allocator() = default;
};

} // namespace MACE::SimulationG4
