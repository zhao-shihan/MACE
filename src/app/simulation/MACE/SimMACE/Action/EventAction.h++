#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4UserEventAction.hh"

namespace MACE::SimMACE::inline Action {

class EventAction final : public Env::Memory::PassiveSingleton<EventAction>,
                          public G4UserEventAction {
public:
    auto EndOfEventAction(const G4Event*) -> void override;
};

} // namespace MACE::SimMACE::inline Action
