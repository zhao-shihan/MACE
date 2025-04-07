#pragma once

#include "MACE/Simulation/Hit/VetoPMHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class VetoPMSD : public Mustard::NonMoveableBase,
                 public G4VSensitiveDetector {
public:
    VetoPMSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

    auto NOpticalPhotonHit() const -> std::unordered_map<int, int>;
    auto NOpticalPhotonOnEachSiPM() const -> std::unordered_map<int, std::vector<int>>;

protected:
    std::unordered_map<int, std::vector<std::unique_ptr<VetoPMHit>>> fHit;
    VetoPMHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
