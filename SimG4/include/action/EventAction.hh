#pragma once

#include "G4UserEventAction.hh"

#include "SimG4Global.hh"

class MACE::SimG4::EventAction : public G4UserEventAction {
public:
    EventAction();
    ~EventAction();

    void BeginOfEventAction(const G4Event*) override;
    void   EndOfEventAction(const G4Event*) override;
};
