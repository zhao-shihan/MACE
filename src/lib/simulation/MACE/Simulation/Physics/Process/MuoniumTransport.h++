#pragma once

#include "MACE/Extension/Geant4X/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Muonium.h++"
#include "MACE/Math/Random/Distribution/Exponential.h++"
#include "MACE/Math/Random/Distribution/Gaussian3DDiagnoal.h++"
#include "MACE/Math/Random/Generator/Xoshiro256Plus.h++"
#include "MACE/Simulation/Physics/MuoniumPhysicsMessenger.h++"
#include "MACE/Simulation/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4ParticleChange.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4VContinuousProcess.hh"
#include "G4VSolid.hh"
#include "Randomize.hh"

#include "muc/utility"

#include <random>

namespace MACE::inline Simulation::inline Physics::inline Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumTransport final : public NonMoveableBase,
                               public G4VContinuousProcess {
public:
    MuoniumTransport();

    auto ManipulateAllSteps(G4bool val) -> void { fManipulateAllSteps = val; }

    auto IsApplicable(const G4ParticleDefinition&) -> G4bool override;
    auto AlongStepDoIt(const G4Track& track, const G4Step&) -> G4VParticleChange* override;

private:
    auto GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double&) -> G4double override;
    auto ProposeRandomFlight(const G4Track& track) -> void;

private:
    enum struct TransportStatus {
        Unknown = -1,
        Decaying,
        InsideTargetVolume,
        OutsideTargetVolume
    };

private:
    const ATarget* const fTarget;

    G4bool fManipulateAllSteps;

    G4ParticleChange fParticleChange;
    TransportStatus fTransportStatus;
    G4bool fIsExitingTargetVolume;

    Math::Random::Xoshiro256Plus fXoshiro256Plus;
    Math::Random::Gaussian3DDiagnoalFast<G4ThreeVector> fStandardGaussian3D;

    typename MuoniumPhysicsMessenger<ATarget>::template Register<MuoniumTransport<ATarget>> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics::inline Process

#include "MACE/Simulation/Physics/Process/MuoniumTransport.inl"
