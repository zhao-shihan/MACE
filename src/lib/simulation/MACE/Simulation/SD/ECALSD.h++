#pragma once

#include "MACE/Simulation/Hit/ECALHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

#include <unordered_map>

namespace MACE::inline Simulation::inline SD {

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

    std::unordered_map<int, muc::unique_ptrvec<ECALHit>> fSplitHit;
    ECALHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
