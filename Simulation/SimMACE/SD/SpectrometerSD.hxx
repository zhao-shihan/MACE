#pragma once

#include <map>

#include "G4TwoVector.hh"
#include "G4VSensitiveDetector.hh"

#include "ObserverPtr.hxx"
#include "SimMACE/Hit/SpectrometerHit.hxx"

class MACE::SimMACE::SpectrometerSD final :
    public G4VSensitiveDetector {
    friend DetectorConstruction;

private:
    SpectrometerSD(const G4String& sdName);
    ~SpectrometerSD() noexcept = default;
    SpectrometerSD(const SpectrometerSD&) = delete;
    SpectrometerSD& operator=(const SpectrometerSD&) = delete;

public:
    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    SpectrometerHitCollection* fHitsCollection;
    std::map<ObserverPtr<const G4Track>, const G4StepPoint> fMonitoringTrackList;
    std::vector<G4TwoVector> fSenseWireMap;
};
