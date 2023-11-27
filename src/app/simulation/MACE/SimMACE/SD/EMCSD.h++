#pragma once

#include "MACE/SimMACE/Hit/EMCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <unordered_map>
#include <vector>

namespace MACE::SimMACE::inline SD {

class EMCSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    EMCSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* theStep, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void EventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    std::unordered_map<int, EMCHit*> fHit;
    EMCHitCollection* fHitsCollection;
};

} // namespace MACE::SimMACE::inline SD
