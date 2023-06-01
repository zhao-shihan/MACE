#pragma once

#include "MACE/SimMACE/Hit/EMCalHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

namespace MACE::SimMACE::inline SD {

class EMCalSD final : public NonMoveableBase,
                      public G4VSensitiveDetector {
public:
    EMCalSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* theStep, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void EventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    EMCalHitCollection* fHitsCollection;
};

} // namespace MACE::SimMACE::inline SD
