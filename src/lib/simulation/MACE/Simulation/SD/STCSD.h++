#pragma once

#include "MACE/Simulation/Hit/STCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class STCSiPMSD;

class STCSD : public NonMoveableBase,
              public G4VSensitiveDetector {
public:
    STCSD(const G4String& sdName, const STCSiPMSD* stcSiPMSD = {});

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    const STCSiPMSD* const fSTCSiPMSD;

    double fEnergyDepositionThreshold;

    std::unordered_map<int, std::vector<std::unique_ptr<STCHit>>> fSplitHit;
    STCHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
