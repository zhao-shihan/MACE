#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/SpectrometerHit.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"

class MACE::SimMACE::SD::Spectrometer final :
    public G4VSensitiveDetector {
public:
    Spectrometer(const G4String& SDName, const G4String& hitsCollectionName, const Geometry::Entity::Fast::SpectrometerCells* spectrometerCellEntity);
    ~Spectrometer() noexcept = default;

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    auto FindMonitoring(const G4Track* track) { return std::find_if(fMonitoringTrackList.cbegin(), fMonitoringTrackList.cend(), [&track](const auto& monitoring) { return track == std::get<0>(monitoring); }); }

private:
    Hit::SpectrometerHitCollection* fHitsCollection;
    const Geometry::Entity::Fast::SpectrometerCells* fSpectrometerCellEntity;
    std::vector<std::tuple<const G4Track*, G4double, G4ThreeVector>> fMonitoringTrackList;
};