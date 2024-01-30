#pragma once

#include "MACE/SimEMC/Hit/EMCPMTHit.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

namespace MACE::SimEMC::inline SD {

class EMCPMTSD final : public NonMoveableBase,
                       public G4VSensitiveDetector {
public:
    EMCPMTSD(const G4String& sdName);

    auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    auto EndOfEvent(G4HCofThisEvent*) -> void override;

    /// Inform this SD of event id in EventAction
    auto EventID(G4int eventID) -> void { fEventID = eventID; }

private:
    G4int fEventID;
    std::unordered_map<int, std::unique_ptr<EMCPMTHit>> fHit;
    EMCPMTHitCollection* fHitsCollection;
};

} // namespace MACE::SimEMC::inline SD
