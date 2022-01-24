#pragma once

#include "G4UserRunAction.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Action::RunAction : public G4UserRunAction {
public:
    RunAction(PrimaryGeneratorAction* pPrimaryGeneratorAction, EventAction* pEventAction);
    ~RunAction();

    void BeginOfRunAction(const G4Run* run) override;
    void   EndOfRunAction(const G4Run*) override;

private:
    PrimaryGeneratorAction* const fpPrimaryGeneratorAction;
    EventAction* const fpEventAction;
    Analysis* const fpAnalysis;
};
