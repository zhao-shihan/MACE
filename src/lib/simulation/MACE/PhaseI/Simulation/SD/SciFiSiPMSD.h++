#pragma once

#include "MACE/PhaseI/Simulation/Hit/SciFiSiPMRawHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

#include <unordered_map>
#include <utility>

namespace MACE::PhaseI::inline Simulation::inline SD {

class SciFiSiPMSD : public Mustard::NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    SciFiSiPMSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

    auto NOpticalPhotonHit() const -> std::unordered_map<int, int>;

protected:
    std::unordered_map<int, muc::unique_ptrvec<SciFiSiPMRawHit>> fHit;
    SciFiSiPMRawHitCollection* fHitsCollection;
};

} // namespace MACE::PhaseI::inline Simulation::inline SD
