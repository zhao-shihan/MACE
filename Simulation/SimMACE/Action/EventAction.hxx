#pragma once

#include "G4UserEventAction.hh"

#include "ObserverPtr.hxx"
#include "SimMACE/Global.hxx"

class MACE::SimMACE::EventAction final :
    public G4UserEventAction {
    friend ActionInitialization;

private:
    EventAction() = default;
    ~EventAction() noexcept = default;
    EventAction(const EventAction&) = delete;
    EventAction& operator=(const EventAction&) = delete;

public:
    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event*) override;
};
