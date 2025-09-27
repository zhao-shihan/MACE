#pragma once

#include "MACE/Simulation/Hit/TTCSiPMHit.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/hash_map"
#include "muc/ptrvec"

#include <vector>

namespace MACE::inline Simulation::inline SD {

enum struct DetectorSiPMType {
    TTCSiPM,        
    PhaseITTCSiPM      
};

class TTCSiPMSD : public G4VSensitiveDetector {
public:
    TTCSiPMSD(const G4String& sdName, const DetectorSiPMType type);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

    auto NOpticalPhotonHit() const -> muc::flat_hash_map<int, std::vector<int>>;

protected:
    DetectorSiPMType detectorSiPMType;
    muc::flat_hash_map<int, muc::unique_ptrvec<TTCSiPMHit>> fHit;
    TTCSiPMHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
