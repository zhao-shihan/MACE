#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/VertexDetectorHit.hxx"

class MACE::SimMACE::VertexDetectorSD final :
    public G4VSensitiveDetector {
public:
    VertexDetectorSD(const G4String& SDName, const G4String& hitsCollectionName);
    ~VertexDetectorSD() noexcept = default;

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    VertexDetectorHitCollection* fHitsCollection;
};
