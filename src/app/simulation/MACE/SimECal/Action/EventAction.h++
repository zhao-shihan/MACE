#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4UserEventAction.hh"

namespace MACE::SimECal::inline Action {

class EventAction final : public Mustard::Env::Memory::PassiveSingleton<EventAction>,
                          public G4UserEventAction {
public:
    auto BeginOfEventAction(const G4Event*) -> void override;
    auto EndOfEventAction(const G4Event*) -> void override;
};

} // namespace MACE::SimECal::inline Action
