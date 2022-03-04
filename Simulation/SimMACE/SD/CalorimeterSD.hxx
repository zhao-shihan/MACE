#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/CalorimeterHit.hxx"

class MACE::SimMACE::CalorimeterSD final :
    public G4VSensitiveDetector {
    friend DetectorConstruction;
private:
    CalorimeterSD(const G4String& sdName);
    ~CalorimeterSD() noexcept = default;
    CalorimeterSD(const CalorimeterSD&) = delete;
    CalorimeterSD& operator=(const CalorimeterSD&) = delete;

public:
    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    CalorimeterHitCollection* fHitsCollection;
};
