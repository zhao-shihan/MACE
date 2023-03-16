#pragma once

#include "MACE/SimMACE/Hit/CDCHit.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VSensitiveDetector.hh"

#include <map>

namespace MACE::SimMACE::SD {

using Hit::CDCHitCollection;

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
    std::map<std::pair<int, int>, const G4StepPoint> fEnteredPointList;
    std::vector<std::pair<G4TwoVector, G4ThreeVector>> fCellMap;
};

} // namespace MACE::SimMACE::SD
