#pragma once

#include "MACE/Simulation/Hit/VetoHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class VetoPMSD;

class VetoSD : public Mustard::NonMoveableBase,
              public G4VSensitiveDetector {
public:
    VetoSD(const G4String& sdName, const VetoPMSD* vetoPMSD = {});

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    const VetoPMSD* const fVetoPMSD;

    double fEnergyDepositionThreshold;

    std::unordered_map<int, std::vector<std::unique_ptr<VetoHit>>> fSplitHit;
    VetoHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
