#pragma once

#include "SimMACE/Hit/VertexDetectorHit.hxx"

#include "G4VSensitiveDetector.hh"

namespace MACE::Simulation::SimMACE::SD {

using Hit::VertexDetectorHitCollection;

class VertexDetectorSD final : public G4VSensitiveDetector {
public:
    VertexDetectorSD(const G4String& sdName);
    ~VertexDetectorSD() noexcept = default;
    VertexDetectorSD(const VertexDetectorSD&) = delete;
    VertexDetectorSD& operator=(const VertexDetectorSD&) = delete;

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    VertexDetectorHitCollection* fHitsCollection;
};

} // namespace MACE::Simulation::SimMACE::SD
