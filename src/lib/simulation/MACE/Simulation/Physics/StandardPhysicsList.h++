#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "QBBC.hh"

namespace MACE::inline Simulation::inline Physics {

class StandardPhysicsListBase : public QBBC {
public:
    StandardPhysicsListBase();
    virtual ~StandardPhysicsListBase() override = default;
};

class StandardPhysicsList final : public Mustard::Env::Memory::PassiveSingleton<StandardPhysicsList>,
                                  public StandardPhysicsListBase {};

} // namespace MACE::inline Simulation::inline Physics
