#pragma once

#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Simulation/SD/MCPSDMessenger.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include <algorithm>
#include <memory>
#include <vector>

namespace MACE::inline Simulation::inline SD {

class MCPSD : public NonMoveableBase,
              public G4VSensitiveDetector {
public:
    MCPSD(const G4String& sdName);

    auto IonizingEnergyDepositionThreshold(double e) -> void { fIonizingEnergyDepositionThreshold = std::max(0., e); }

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    double fIonizingEnergyDepositionThreshold;

    std::vector<std::unique_ptr<MCPHit>> fSplitHit;
    MCPHitCollection* fHitsCollection;

    MCPSDMessenger::Register<MCPSD> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline SD
