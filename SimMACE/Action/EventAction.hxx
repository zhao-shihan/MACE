#pragma once

#include "G4UserEventAction.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::EventAction final :
    public G4UserEventAction {
public:
    EventAction() = default;
    ~EventAction() noexcept = default;
    EventAction(const EventAction&) = delete;
    EventAction& operator=(const EventAction&) = delete;

    void EndOfEventAction(const G4Event*) override;
};
