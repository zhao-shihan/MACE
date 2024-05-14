#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4VUserActionInitialization.hh"

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

class ActionInitialization final : public Env::Memory::PassiveSingleton<ActionInitialization>,
                                   public G4VUserActionInitialization {
public:
    auto Build() const -> void override;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
