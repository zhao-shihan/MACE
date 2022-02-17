#pragma once

#include "G4UserRunAction.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::Action::RunAction final :
    public G4UserRunAction {
public:
    RunAction(ObserverPtr<PrimaryGeneratorAction> primaryGeneratorAction, ObserverPtr<EventAction> eventAction);
    ~RunAction() noexcept = default;

    void BeginOfRunAction(const G4Run* run) override;
    void   EndOfRunAction(const G4Run*) override;

private:
    const ObserverPtr<PrimaryGeneratorAction> fPrimaryGeneratorAction;
    const ObserverPtr<EventAction> fEventAction;
};
