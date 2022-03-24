#pragma once

#include "SimMACE/Hit/CalorimeterHit.hxx"

#include "G4VSensitiveDetector.hh"

namespace MACE::Simulation::SimMACE::SD {

using Hit::CalorimeterHitCollection;

class CalorimeterSD final : public G4VSensitiveDetector {
public:
    CalorimeterSD(const G4String& sdName);
    ~CalorimeterSD() noexcept = default;
    CalorimeterSD(const CalorimeterSD&) = delete;
    CalorimeterSD& operator=(const CalorimeterSD&) = delete;

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    CalorimeterHitCollection* fHitsCollection;
};

} // namespace MACE::Simulation::SimMACE::SD
