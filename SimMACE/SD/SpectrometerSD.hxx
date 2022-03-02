#pragma once

#include "G4VSensitiveDetector.hh"
#include "G4TwoVector.hh"

#include "SimMACE/Hit/SpectrometerHit.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::SpectrometerSD final :
    public G4VSensitiveDetector {
    friend DetectorConstruction;
private:
    SpectrometerSD(const G4String& SDName, const G4String& hitsCollectionName);
    ~SpectrometerSD() noexcept = default;
    SpectrometerSD(const SpectrometerSD&) = delete;
    SpectrometerSD& operator=(const SpectrometerSD&) = delete;

public:
    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    auto FindMonitoring(ObserverPtr<const G4Track> track) { return std::ranges::find_if(std::as_const(fMonitoringTrackList), [&track](const auto& monitoring) { return track == std::get<0>(monitoring); }); }

private:
    SpectrometerHitCollection* fHitsCollection;
    std::vector<std::tuple<ObserverPtr<const G4Track>, G4double, G4ThreeVector>> fMonitoringTrackList;
    const std::vector<std::tuple<int, double, G4TwoVector>> fSpectrometerSensitiveVolumeInfoList;
};
