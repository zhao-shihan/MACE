#pragma once

#include "MACE/Simulation/Hit/TTCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class TTCSiPMSD;

class TTCSD : public NonMoveableBase,
              public G4VSensitiveDetector {
public:
    TTCSD(const G4String& sdName, const TTCSiPMSD* ttcSiPMSD = {});

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    const TTCSiPMSD* const fTTCSiPMSD;

    double fEnergyDepositionThreshold;

    std::unordered_map<int, std::vector<std::unique_ptr<TTCHit>>> fSplitHit;
    TTCHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
