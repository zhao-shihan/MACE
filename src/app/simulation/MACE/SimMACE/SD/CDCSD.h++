#pragma once

#include "MACE/Detector/Description/CDC.h++"
#include "MACE/SimMACE/Hit/CDCHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MACE::SimMACE::inline SD {

class CDCSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    CDCSD(const G4String& sdName);

    auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    auto EndOfEvent(G4HCofThisEvent*) -> void override;

    /// @brief Inform this SD of event ID in EventAction
    auto EventID(G4int eventID) -> void { fEventID = eventID; }

private:
    G4int fEventID;

    double fMeanDriftVelocity;
    const std::vector<Detector::Description::CDC::CellInformation>* fCellMap;

    std::unordered_map<int, std::vector<std::unique_ptr<CDCHit>>> fSplitHit;
    CDCHitCollection* fHitsCollection;
};

} // namespace MACE::SimMACE::inline SD
