#pragma once

#include "G4UserEventAction.hh"

#include "SimMACE/Global.hxx"
#include "ObserverPtr.hxx"

class MACE::SimMACE::EventAction final :
    public G4UserEventAction {
    friend ActionInitialization;
private:
    EventAction() = default;
    ~EventAction() noexcept = default;
    EventAction(const EventAction&) = delete;
    EventAction& operator=(const EventAction&) = delete;

public:
    void EndOfEventAction(const G4Event*) override;
};
