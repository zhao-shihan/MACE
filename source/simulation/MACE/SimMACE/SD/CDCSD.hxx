#pragma once

#include "MACE/SimMACE/Hit/CDCHit.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VSensitiveDetector.hh"

#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace MACE::SimMACE::inline SD {

class CDCSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    CDCSD(const G4String& sdName);

    void Initialize(G4HCofThisEvent* hitsCollection) override;
    G4bool ProcessHits(G4Step* theStep, G4TouchableHistory*) override;
    void EndOfEvent(G4HCofThisEvent*) override;

    /// @brief Inform this SD of event ID in EventAction
    void SetEventID(G4int eventID) { fEventID = eventID; }

private:
    G4int fEventID;
    CDCHitCollection* fHitsCollection;

    G4double fMeanDriftVelocity;
    G4double fHalfTimeResolution;

    std::vector<std::map<int, const G4StepPoint>> fCellEntryPoints;
    std::vector<std::pair<const G4TwoVector, const G4ThreeVector>> fCellMap;
    std::vector<std::vector<std::pair<double, std::unique_ptr<CDCHit>>>> fCellSignalTimesAndHits;
};

} // namespace MACE::SimMACE::inline SD
