#pragma once

#include "MACE/Simulation/SimMACE/Hit/MCPHit.hxx"

#include "G4VSensitiveDetector.hh"

namespace MACE::Simulation::SimMACE::SD {

using Hit::MCPHitCollection;

class MCPSD final : public G4VSensitiveDetector {
public:
    MCPSD(const G4String& sdName);
    ~MCPSD() noexcept = default;
    MCPSD(const MCPSD&) = delete;
    MCPSD& operator=(const MCPSD&) = delete;

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    MCPHitCollection* fHitsCollection;
};

} // namespace MACE::Simulation::SimMACE::SD
