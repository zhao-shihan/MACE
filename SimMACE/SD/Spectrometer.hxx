#pragma once

#include "G4VSensitiveDetector.hh"

#include "SimMACE/Hit/SpectrometerHit.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::SD::Spectrometer final :
    public G4VSensitiveDetector {
public:
    Spectrometer(const G4String& SDName, const G4String& hitsCollectionName, const std::shared_ptr<const Geometry::Entity::Fast::SpectrometerCells>& spectrometerCellEntity);
    ~Spectrometer() noexcept = default;

    void   Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void   EndOfEvent(G4HCofThisEvent*) override;

private:
    inline auto FindMonitoring(ObserverPtr<const G4Track> track);

private:
    Hit::SpectrometerHitCollection* fHitsCollection;
    std::shared_ptr<const Geometry::Entity::Fast::SpectrometerCells> fSpectrometerCellEntity;
    std::vector<std::tuple<ObserverPtr<const G4Track>, G4double, G4ThreeVector>> fMonitoringTrackList;
};

inline auto MACE::SimMACE::SD::Spectrometer::FindMonitoring(ObserverPtr<const G4Track> track) {
    return std::find_if(fMonitoringTrackList.cbegin(), fMonitoringTrackList.cend(),
        [&track](const auto& monitoring) {
            return track == std::get<0>(monitoring);
        }
    );
}
