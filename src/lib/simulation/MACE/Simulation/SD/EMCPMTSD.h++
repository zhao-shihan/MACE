#pragma once

#include "MACE/Simulation/Hit/EMCPMTHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class EMCPMTSD : public NonMoveableBase,
                 public G4VSensitiveDetector {
public:
    EMCPMTSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

    auto NOpticalPhotonHit() const -> const auto& { return fNHit; }

    /// Inform this SD of event id in EventAction
    auto EventID(G4int eventID) -> void { fEventID = eventID; }

protected:
    G4int fEventID;

    std::unordered_map<int, std::vector<std::unique_ptr<EMCPMTHit>>> fHit;
    std::vector<std::pair<int, int>> fNHit;
    EMCPMTHitCollection* fHitsCollection;
};

} // namespace MACE::inline Simulation::inline SD
