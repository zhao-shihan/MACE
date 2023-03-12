#pragma once

#include "MACE/SimMACE/Hit/EMCalHit.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VSensitiveDetector.hh"

namespace MACE::SimMACE::SD {

using Hit::EMCalHitCollection;

class EMCalSD final : public NonMoveableBase,
                      public G4VSensitiveDetector {
public:
    EMCalSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    EMCalHitCollection* fHitsCollection;
};

} // namespace MACE::SimMACE::SD
