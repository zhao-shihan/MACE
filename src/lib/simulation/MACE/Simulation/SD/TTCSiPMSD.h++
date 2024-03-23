#pragma once

#include "MACE/Simulation/Hit/TTCSiPMHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class TTCSiPMSD : public NonMoveableBase,
                  public G4VSensitiveDetector {
public:
    TTCSiPMSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

    auto NOpticalPhotonHit() const -> std::unordered_map<int, int>;

protected:
    std::unordered_map<int, std::vector<std::unique_ptr<TTCSiPMHit>>> fHit;
    TTCSiPMHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
