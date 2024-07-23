#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4UserSteppingAction.hh"

namespace MACE::SimDose::inline Action {

class SteppingAction final : public Mustard::Env::Memory::PassiveSingleton<SteppingAction>,
                             public G4UserSteppingAction {
public:
    auto UserSteppingAction(const G4Step* step) -> void override;
};

} // namespace MACE::SimDose::inline Action
