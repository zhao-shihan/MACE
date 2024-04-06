#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4ParticleDefinition.hh"

namespace MACE::inline Extension::Geant4X {

class Antimuonium final : public Env::Memory::Singleton<Antimuonium>,
                          public G4ParticleDefinition {
    friend Env::Memory::SingletonInstantiator;

private:
    Antimuonium();

public:
    static auto Definition() -> auto { return &Instance(); }
};

} // namespace MACE::inline Extension::Geant4X
