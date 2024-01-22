#pragma once

<<<<<<<< HEAD:src/app/simulation/MACE/SimEMC/SD/MCPSD.h++
#include "MACE/SimEMC/Hit/MCPHit.h++"
========
// #include "MACE/SimEMC/Hit/EMCRawHit.h++"
#include "MACE/SimEMC/Hit/EMCHit.h++"
>>>>>>>> dev:src/app/simulation/MACE/SimEMC/SD/EMCSD.h++
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

namespace MACE::SimEMC::inline SD {

<<<<<<<< HEAD:src/app/simulation/MACE/SimEMC/SD/MCPSD.h++
class MCPSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    MCPSD(const G4String& sdName);
========
class EMCSD final : public NonMoveableBase,
                    public G4VSensitiveDetector {
public:
    EMCSD(G4String name);
>>>>>>>> dev:src/app/simulation/MACE/SimEMC/SD/EMCSD.h++

    auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    auto EndOfEvent(G4HCofThisEvent*) -> void override;

    /// Inform this SD of event id in EventAction
    auto EventID(G4int eventID) -> void { fEventID = eventID; }

private:
<<<<<<<< HEAD:src/app/simulation/MACE/SimEMC/SD/MCPSD.h++
    G4int fEventID;
    MCPHitCollection* fHitsCollection;
========
    EMCHitCollection* fHitsCollection;
    // EMCRawHit fEMCRawHit;
>>>>>>>> dev:src/app/simulation/MACE/SimEMC/SD/EMCSD.h++
};

} // namespace MACE::SimEMC::inline SD
