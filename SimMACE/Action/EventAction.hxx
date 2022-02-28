#pragma once

#include "G4UserEventAction.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::EventAction final :
    public G4UserEventAction {
    friend RunManager;
private:
    EventAction() = default;
    ~EventAction() noexcept = default;

public:
    EventAction(const EventAction&) = delete;
    EventAction& operator=(const EventAction&) = delete;

    void EndOfEventAction(const G4Event*) override;
};
