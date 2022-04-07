#pragma once

#include "Simulation/SimMACE/Hit/SpectrometerHit.hxx"
#include "Utility/ObserverPtr.hxx"

#include "G4TwoVector.hh"
#include "G4VSensitiveDetector.hh"

#include <map>

namespace MACE::Simulation::SimMACE::SD {

using Hit::SpectrometerHitCollection;
using MACE::Utility::ObserverPtr;

class SpectrometerSD final : public G4VSensitiveDetector {
public:
    SpectrometerSD(const G4String& sdName);
    ~SpectrometerSD() noexcept = default;
    SpectrometerSD(const SpectrometerSD&) = delete;
    SpectrometerSD& operator=(const SpectrometerSD&) = delete;

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    SpectrometerHitCollection* fHitsCollection;
    std::map<std::pair<int, int>, const G4StepPoint> fEnteredPointList;
    std::vector<std::pair<G4TwoVector, G4ThreeVector>> fSenseWireMap;
};

} // namespace MACE::Simulation::SimMACE::SD
