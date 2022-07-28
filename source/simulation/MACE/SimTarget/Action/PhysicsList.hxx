#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VModularPhysicsList.hh"

namespace MACE::SimTarget::Action {

class PhysicsList final : public Utility::NonMoveableBase,
                          public G4VModularPhysicsList {
public:
    PhysicsList();
};

} // namespace MACE::SimTarget::Action
