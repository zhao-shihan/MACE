#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/VertexDetectorHit.hxx"

class MACE::SimMACE::SD::VertexDetector : public G4VSensitiveDetector {
public:
    VertexDetector(const G4String& SDName, const G4String& hitsCollectionName);
    ~VertexDetector();

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    Hit::VertexDetectorHitCollection* fHitsCollection;
};
