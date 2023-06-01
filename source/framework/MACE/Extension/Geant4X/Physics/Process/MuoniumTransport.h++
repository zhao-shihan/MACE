#pragma once

#include "MACE/Compatibility/std2b/unreachable.h++"
#include "MACE/Extension/Geant4X/Physics/Messenger/MuoniumPhysicsMessenger.h++"
#include "MACE/Extension/Geant4X/Physics/Particle/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.h++"
#include "MACE/Extension/Geant4X/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Math/Random/Distribution/Exponential.h++"
#include "MACE/Math/Random/Distribution/Gaussian3DDiagnoal.h++"
#include "MACE/Math/Random/Generator/Xoshiro256Plus.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4ParticleChange.hh"
#include "G4ThreeVector.hh"
#include "G4VContinuousProcess.hh"
#include "Randomize.hh"

#include <random>

namespace MACE::inline Extension::Geant4X::Physics::inline Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumTransport final : public NonMoveableBase,
                               public G4VContinuousProcess {
public:
    MuoniumTransport();

    void MeanFreePath(G4double val) { fMeanFreePath = val; }
    void ManipulateAllSteps(G4bool val) { fManipulateAllSteps = val; }

    G4bool IsApplicable(const G4ParticleDefinition&) override;
    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step&) override;

private:
    G4double GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double&) override;
    void ProposeRandomFlight(const G4Track& track);

private:
    enum class TransportStatus {
        Unknown = -1,
        Decaying,
        InsideTargetVolume,
        ExitingTargetVolume,
        OutsideTargetVolume
    };

private:
    const ATarget* const fTarget;

    G4double fMeanFreePath;
    G4bool fManipulateAllSteps;

    G4ParticleChange fParticleChange;
    TransportStatus fTransportStatus;
    G4bool fIsExitingTargetVolume;
};

} // namespace MACE::inline Extension::Geant4X::Physics::inline Process

#include "MACE/Extension/Geant4X/Physics/Process/MuoniumTransport.inl"
