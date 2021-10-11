#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimG4/hit/SpectrometerHit.hh"

class MACE::SimG4::SD::Spectrometer : public G4VSensitiveDetector {
public:
    Spectrometer(const G4String& SDName, const G4String& hitsCollectionName);
    ~Spectrometer();

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    Hit::CollectionOfSpectrometer* fHitsCollection;
};
