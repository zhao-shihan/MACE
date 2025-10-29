#pragma once

#include "MACE/Simulation/Hit/MCPHit.h++"
#include "MACE/Simulation/SD/MCPSDMessenger.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

#include <algorithm>

class G4DataInterpolation;

namespace MACE::inline Simulation::inline SD {

class MCPSD : public G4VSensitiveDetector {
public:
    explicit MCPSD(const G4String& sdName);
    ~MCPSD() override;

    auto IonizingEnergyDepositionThreshold(double e) -> void { fIonizingEnergyDepositionThreshold = std::max(0., e); }

    auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    double fIonizingEnergyDepositionThreshold;

    std::unique_ptr<G4DataInterpolation> fEfficiency;

    muc::unique_ptrvec<MCPHit> fSplitHit;
    MCPHitCollection* fHitsCollection;

    MCPSDMessenger::Register<MCPSD> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline SD
