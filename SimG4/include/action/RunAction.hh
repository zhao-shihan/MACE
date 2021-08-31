#pragma once

#include "G4UserRunAction.hh"

#include "SimG4Global.hh"

class RunAction : public G4UserRunAction {
public:
    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;
};
