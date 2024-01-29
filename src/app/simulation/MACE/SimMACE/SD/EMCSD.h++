#pragma once

#include "MACE/SimMACE/Hit/EMCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::SimMACE::inline SD {

class EMCSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    EMCSD(const G4String& sdName);

    auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    auto EndOfEvent(G4HCofThisEvent*) -> void override;

    /// Inform this SD of event id in EventAction
    auto EventID(G4int eventID) -> void { fEventID = eventID; }

private:
    G4int fEventID;

    std::unordered_map<int, std::vector<std::unique_ptr<EMCHit>>> fSplitHit;
    EMCHitCollection* fHitsCollection;
};

} // namespace MACE::SimMACE::inline SD
