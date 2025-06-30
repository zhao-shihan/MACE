#pragma once

#include "MACE/PhaseI/Simulation/Hit/SciFiHit.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

#include <unordered_map>
#include <utility>

namespace MACE::PhaseI::inline Simulation::inline SD {

class SciFiSD : public G4VSensitiveDetector {
public:
    SciFiSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    std::unordered_map<int, muc::unique_ptrvec<SciFiHit>> fSplitHit;
    SciFiHitCollection* fHitsCollection;
};

} // namespace MACE::PhaseI::inline Simulation::inline SD
