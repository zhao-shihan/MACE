#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "FTFP_BERT.hh"

namespace MACE::SimMACE {

class PhysicsList final : public Env::Memory::PassiveSingleton<PhysicsList>,
                          public FTFP_BERT {
public:
    PhysicsList();
};

} // namespace MACE::SimMACE
