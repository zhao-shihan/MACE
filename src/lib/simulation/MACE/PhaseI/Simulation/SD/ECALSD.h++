#pragma once

#include "MACE/PhaseI/Simulation/Hit/ECALHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::PhaseI::inline Simulation::inline SD {

class ECALPMSD;

class ECALSD : public Mustard::NonMoveableBase,
               public G4VSensitiveDetector {
public:
    ECALSD(const G4String& sdName, const ECALPMSD* ecalPMSD = {});

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    const ECALPMSD* const fECALPMSD;

    double fEnergyDepositionThreshold;

    std::unordered_map<int, std::vector<std::unique_ptr<ECALHit>>> fSplitHit;
    ECALHitCollection* fHitsCollection;
};

} // namespace MACE::PhaseI::inline Simulation::inline SD
