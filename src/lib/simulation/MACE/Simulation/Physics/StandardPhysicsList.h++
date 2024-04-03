#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "FTFP_BERT.hh"

namespace MACE::inline Simulation::inline Physics {

class StandardPhysicsListBase : public FTFP_BERT {
public:
    StandardPhysicsListBase();
    virtual ~StandardPhysicsListBase() override = default;
};

class StandardPhysicsList final : public Env::Memory::PassiveSingleton<StandardPhysicsList>,
                                  public StandardPhysicsListBase {};

} // namespace MACE::inline Simulation::inline Physics
