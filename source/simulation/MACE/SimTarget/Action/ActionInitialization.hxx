#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4VUserActionInitialization.hh"

namespace MACE::SimTarget::Action {

class ActionInitialization final : public Env::Memory::FreeSingleton<ActionInitialization>,
                                   public G4VUserActionInitialization {
public:
    void Build() const override;
};

} // namespace MACE::SimTarget::Action
