#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/VertexDetectorHit.hxx"

class MACE::SimMACE::VertexDetectorSD final :
    public G4VSensitiveDetector {
    friend DetectorConstruction;

private:
    VertexDetectorSD(const G4String& sdName);
    ~VertexDetectorSD() noexcept = default;
    VertexDetectorSD(const VertexDetectorSD&) = delete;
    VertexDetectorSD& operator=(const VertexDetectorSD&) = delete;

public:
    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    VertexDetectorHitCollection* fHitsCollection;
};
