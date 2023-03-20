#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VModularPhysicsList.hh"

namespace MACE::SimMACE::inline Action {

class PhysicsList final : public NonMoveableBase,
                          public G4VModularPhysicsList {
public:
    PhysicsList();
};

} // namespace MACE::SimMACE::inline Action
