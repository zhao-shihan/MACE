#pragma once

#include "MACE/PhaseI/SimMACEPhaseI/SD/MRPCSDMessenger.h++"
#include "MACE/PhaseI/Simulation/Hit/MRPCHit.h++"

#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

#include <algorithm>

class G4DataInterpolation;

namespace MACE::PhaseI::SimMACEPhaseI::inline SD {

class MRPCSD : public Mustard::NonMoveableBase,
               public G4VSensitiveDetector {
public:
    MRPCSD(const G4String& sdName);
    ~MRPCSD();

    auto IonizingEnergyDepositionThreshold(double e) -> void { fIonizingEnergyDepositionThreshold = std::max(0., e); }

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    double fIonizingEnergyDepositionThreshold;

    std::unordered_map<int, muc::unique_ptrvec<MRPCHit>> fSplitHit;
    MRPCHitCollection* fHitsCollection;

    MRPCSDMessenger::Register<MRPCSD> fMessengerRegister;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline SD
