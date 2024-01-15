#pragma once

#include "MACE/Compatibility/std23/unreachable.h++"
#include "MACE/Math/Random/Distribution/Exponential.h++"
#include "MACE/Math/Random/Distribution/Gaussian3DDiagnoal.h++"
#include "MACE/Math/Random/Generator/Xoshiro256Plus.h++"
#include "MACE/Simulation/Physics/Messenger/MuoniumPhysicsMessenger.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"
#include "MACE/Simulation/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4ParticleChange.hh"
#include "G4ThreeVector.hh"
#include "G4VContinuousProcess.hh"
#include "Randomize.hh"

#include <random>

namespace MACE::inline Simulation::inline Physics::inline Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumTransport final : public NonMoveableBase,
                               public G4VContinuousProcess {
public:
    MuoniumTransport();

    auto MeanFreePath(G4double val) -> void { fMeanFreePath = val; }
    auto ManipulateAllSteps(G4bool val) -> void { fManipulateAllSteps = val; }

    auto IsApplicable(const G4ParticleDefinition&) -> G4bool override;
    auto AlongStepDoIt(const G4Track& track, const G4Step&) -> G4VParticleChange* override;

private:
    auto GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double&) -> G4double override;
    auto ProposeRandomFlight(const G4Track& track) -> void;

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

} // namespace MACE::inline Simulation::inline Physics::inline Process

#include "MACE/Simulation/Physics/Process/MuoniumTransport.inl"
