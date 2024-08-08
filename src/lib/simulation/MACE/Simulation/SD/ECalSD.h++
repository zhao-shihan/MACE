#pragma once

#include "MACE/Simulation/Hit/ECalHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class ECalPMTSD;

class ECalSD : public Mustard::NonMoveableBase,
              public G4VSensitiveDetector {
public:
    ECalSD(const G4String& sdName, const ECalPMTSD* eCalPMTSD = {});

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    const ECalPMTSD* const fECalPMTSD;

    double fEnergyDepositionThreshold;

    std::unordered_map<int, std::vector<std::unique_ptr<ECalHit>>> fSplitHit;
    ECalHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
