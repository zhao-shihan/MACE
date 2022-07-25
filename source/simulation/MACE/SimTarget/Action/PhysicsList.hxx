#pragma once

#include "MACE/Utility/NonCopyableBase.hxx"

#include "G4VModularPhysicsList.hh"

namespace MACE::SimTarget::Action {

class PhysicsList final : public Utility::NonCopyableBase,
                          public G4VModularPhysicsList {
public:
    PhysicsList();
};

} // namespace MACE::SimTarget::Action
