#pragma once

#include "MACE/SimMACE/Hit/MCPHit.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VSensitiveDetector.hh"

namespace MACE::SimMACE::SD {

using Hit::MCPHitCollection;

class MCPSD final : public Utility::NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    MCPSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    ObserverPtr<MCPHitCollection> fHitsCollection;
};

} // namespace MACE::SimMACE::SD
