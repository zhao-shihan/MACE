#pragma once

#include "MACE/SimEMC/Hit/EMCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

namespace MACE::SimEMC::inline SD {

class SiPMSD final : public NonMoveableBase,
                     public G4VSensitiveDetector {
public:
    SiPMSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* theStep, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void EventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    SiPMHitCollection* fHitsCollection;
};

} // namespace MACE::SimEMC::inline SD
