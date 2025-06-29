#pragma once

#include "MACE/Simulation/Hit/ECALPMHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

#include <unordered_map>
#include <utility>

namespace MACE::inline Simulation::inline SD {

class ECALPMSD : public Mustard::NonMoveableBase,
                 public G4VSensitiveDetector {
public:
    ECALPMSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

    auto NOpticalPhotonHit() const -> std::unordered_map<int, int>;

protected:
    std::unordered_map<int, muc::unique_ptrvec<ECALPMHit>> fHit;
    ECALPMHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
