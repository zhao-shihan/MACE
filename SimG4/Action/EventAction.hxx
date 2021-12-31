#pragma once

#include "G4UserEventAction.hh"

#include "SimG4/Global.hxx"

class MACE::SimG4::Action::EventAction final : public G4UserEventAction {
public:
    EventAction();
    ~EventAction();

    void SetFirstTrueEventIDOfThisRank(G4int trueEventID) { fFirstTrueEventIDOfThisRank = trueEventID; }

    void BeginOfEventAction(const G4Event* event) override;
    void   EndOfEventAction(const G4Event*) override;

private:
    G4int fFirstTrueEventIDOfThisRank = 0;
};
