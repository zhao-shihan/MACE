#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UserEventAction.hh"

namespace MACE::Simulation::SimMACE::Action {

class EventAction final : public G4UserEventAction {
public:
    EventAction() = default;
    ~EventAction() noexcept = default;
    EventAction(const EventAction&) = delete;
    EventAction& operator=(const EventAction&) = delete;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event*) override;
};

} // namespace MACE::Simulation::SimMACE::Action
