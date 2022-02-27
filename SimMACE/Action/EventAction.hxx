#pragma once

#include "G4UserEventAction.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::EventAction final :
    public G4UserEventAction {
public:
    EventAction(ObserverPtr<const RunAction> runAction);
    ~EventAction() noexcept = default;

    void BeginOfEventAction(const G4Event* event) override;
    void   EndOfEventAction(const G4Event*) override;

    auto GetTrueEventID() const { return fTrueEventID; }

private:
    const ObserverPtr<const RunAction> fRunAction;

    G4int fTrueEventID;
};
