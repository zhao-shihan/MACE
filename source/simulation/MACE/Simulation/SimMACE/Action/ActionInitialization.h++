#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4VUserActionInitialization.hh"

namespace MACE::inline Simulation::SimMACE::inline Action {

class ActionInitialization final : public Env::Memory::PassiveSingleton<ActionInitialization>,
                                   public G4VUserActionInitialization {
public:
    void Build() const override;
};

} // namespace MACE::inline Simulation::SimMACE::inline Action
