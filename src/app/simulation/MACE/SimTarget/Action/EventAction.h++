#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4UserEventAction.hh"

namespace MACE::SimTarget::inline Action {

class EventAction final : public Env::Memory::PassiveSingleton<EventAction>,
                          public G4UserEventAction {
public:
    auto BeginOfEventAction(const G4Event* event) -> void override;
};

} // namespace MACE::SimTarget::inline Action
