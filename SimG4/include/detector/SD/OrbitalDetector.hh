#pragma once

#include "G4VSensitiveDetector.hh"

#include "detector/hit/OrbitalDetector.hh"

class MACE::SimG4::SD::OrbitalDetector : public G4VSensitiveDetector {
public:
    OrbitalDetector(const G4String& SDName, const G4String& hitsCollectionName);
    ~OrbitalDetector();

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    Hit::CollectionOfOrbitalDetector* fHitsCollection;
};
