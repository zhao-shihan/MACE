#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/CalorimeterHit.hxx"

class MACE::SimMACE::SD::Calorimeter final :
    public G4VSensitiveDetector {
public:
    Calorimeter(const G4String& SDName, const G4String& hitsCollectionName);
    ~Calorimeter() noexcept = default;

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    Hit::CalorimeterHitCollection* fHitsCollection;
};
