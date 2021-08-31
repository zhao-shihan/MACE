#pragma once

#include "G4VSensitiveDetector.hh"

#include "detector/hit/CalorimeterHit.hh"

class MACE::SimG4::SD::Calorimeter : public G4VSensitiveDetector {
public:
    Calorimeter(const G4String& SDName, const G4String& hitsCollectionName);
    ~Calorimeter();

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    Hit::CalorimeterHitsCollection* fHitsCollection;
};
