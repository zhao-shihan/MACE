#pragma once

#include "MACE/Simulation/Hit/EMCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class EMCPMTSD;

class EMCSD : public NonMoveableBase,
              public G4VSensitiveDetector {
public:
    EMCSD(const G4String& sdName, const EMCPMTSD* emcPMTSD = {});

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    const EMCPMTSD* const fEMCPMTSD;

    std::unordered_map<int, std::vector<std::unique_ptr<EMCHit>>> fSplitHit;
    EMCHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
