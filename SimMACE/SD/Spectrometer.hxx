#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/SpectrometerHit.hxx"

class MACE::SimMACE::SD::Spectrometer : public G4VSensitiveDetector {
public:
    Spectrometer(const G4String& SDName, const G4String& hitsCollectionName);
    ~Spectrometer();

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    Hit::SpectrometerHitCollection* fHitsCollection;
    const G4Track* fCurrentTrack;
    G4double fInX;
    G4double fInY;
};
