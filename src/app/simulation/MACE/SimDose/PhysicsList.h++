#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "Shielding.hh"

namespace MACE::SimDose {

class PhysicsList : public Shielding {
public:
    PhysicsList();
};

} // namespace MACE::SimDose
