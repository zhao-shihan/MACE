#pragma once

#include "G4UserRunAction.hh"

#include "SimG4Global.hh"

class MACE::SimG4::RunAction : public G4UserRunAction {
public:
    RunAction(const DetectorConstruction* pDetectorConstruction, PrimaryGeneratorAction* pPrimaryGeneratorAction, EventAction* pEventAction);
    ~RunAction();

    void BeginOfRunAction(const G4Run* run) override;
    void   EndOfRunAction(const G4Run*) override;

private:
    const DetectorConstruction* const fpDetectorConstruction;
    PrimaryGeneratorAction* const fpPrimaryGeneratorAction;
    EventAction* const fpEventAction;
};
