#pragma once

#include "G4UserEventAction.hh"

#include "SimG4Global.hh"

class MACE::SimG4::EventAction final : public G4UserEventAction {
public:
    EventAction();
    ~EventAction();

    void SetFirstPluseIDOfThisRank(G4int pluseID) { fFirstPluseIDOfThisRank = pluseID; }

    void BeginOfEventAction(const G4Event* event) override;
    void   EndOfEventAction(const G4Event*) override;

private:
    G4int fFirstPluseIDOfThisRank = 0;
};
