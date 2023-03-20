#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4UserEventAction.hh"

namespace MACE::SimTarget::inline Action {

class EventAction final : public Env::Memory::FreeSingleton<EventAction>,
                          public G4UserEventAction {
public:
    void BeginOfEventAction(const G4Event* event) override;
};

} // namespace MACE::SimTarget::inline Action
