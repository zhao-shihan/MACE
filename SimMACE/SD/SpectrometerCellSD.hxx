#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/SpectrometerHit.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::SpectrometerCellSD final :
    public G4VSensitiveDetector {
    friend DetectorConstruction;
private:
    SpectrometerCellSD(const G4String& SDName, const G4String& hitsCollectionName);
    ~SpectrometerCellSD() noexcept = default;
    SpectrometerCellSD(const SpectrometerCellSD&) = delete;
    SpectrometerCellSD& operator=(const SpectrometerCellSD&) = delete;

public:
    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    auto FindMonitoring(ObserverPtr<const G4Track> track);

private:
    SpectrometerHitCollection* fHitsCollection;
    std::vector<std::tuple<ObserverPtr<const G4Track>, G4double, G4ThreeVector>> fMonitoringTrackList;
};
