#pragma once

#include "MACE/Simulation/SimMACE/Hit/EMCalHit.hxx"

#include "G4VSensitiveDetector.hh"

namespace MACE::Simulation::SimMACE::SD {

using Hit::EMCalHitCollection;

class EMCalSD final : public G4VSensitiveDetector {
public:
    EMCalSD(const G4String& sdName);
    ~EMCalSD() noexcept = default;
    EMCalSD(const EMCalSD&) = delete;
    EMCalSD& operator=(const EMCalSD&) = delete;

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// Inform this SD of event id in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    EMCalHitCollection* fHitsCollection;
};

} // namespace MACE::Simulation::SimMACE::SD
