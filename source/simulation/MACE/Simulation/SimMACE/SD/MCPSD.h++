#pragma once

#include "MACE/Simulation/SimMACE/Hit/MCPHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

namespace MACE::inline Simulation::SimMACE::inline SD {

class MCPSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    MCPSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* theStep, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void EventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    MCPHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::SimMACE::inline SD
