#pragma once

#include "MACE/Environment/Memory/FreeSingleton.hxx"

#include "G4UserEventAction.hh"

namespace MACE::SimTarget::Action {

class EventAction final : public Environment::Memory::FreeSingleton<EventAction>,
                          public G4UserEventAction {
public:
    void BeginOfEventAction(const G4Event* event) override;
};

} // namespace MACE::SimTarget::Action
