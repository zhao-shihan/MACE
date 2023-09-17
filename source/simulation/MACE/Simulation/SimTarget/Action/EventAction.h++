#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4UserEventAction.hh"

namespace MACE::inline Simulation::SimTarget::inline Action {

class EventAction final : public Env::Memory::PassiveSingleton<EventAction>,
                          public G4UserEventAction {
public:
    void BeginOfEventAction(const G4Event* event) override;
};

} // namespace MACE::inline Simulation::SimTarget::inline Action
