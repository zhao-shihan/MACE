#pragma once

// #include "MACE/SimEMC/Hit/EMCRawHit.h++"
#include "MACE/SimEMC/Hit/PMTHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

namespace MACE::SimEMC::inline SD {

class PMTSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    PMTSD(G4String name);

    auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    auto EndOfEvent(G4HCofThisEvent*) -> void override;

private:
    PMTHitCollection* fHitsCollection;
    // EMCRawHit fEMCRawHit;
};

} // namespace MACE::SimEMC::inline SD
