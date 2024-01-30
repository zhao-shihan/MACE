#pragma once

#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

namespace MACE::inline Simulation::inline SD {

class MCPSD : public NonMoveableBase,
              public G4VSensitiveDetector {
public:
    MCPSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;

    /// Inform this SD of event id in EventAction
    auto EventID(G4int eventID) -> void { fEventID = eventID; }

protected:
    G4int fEventID;
    int fHitID;

    MCPHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
