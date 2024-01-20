#pragma once

#include "MACE/Simulation/Physics/MuoniumPhysicsMessenger.h++"
#include "MACE/Simulation/Physics/Particle/Antimuonium.h++"
#include "MACE/Simulation/Physics/Particle/Muonium.h++"
#include "MACE/Simulation/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/NonMoveableBase.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4MuonPlus.hh"
#include "G4ParticleChange.hh"
#include "G4VRestProcess.hh"

#include "gsl/gsl"

#include <limits>

namespace MACE::inline Simulation::inline Physics::inline Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumFormation final : public NonMoveableBase,
                               public G4VRestProcess {
public:
    MuoniumFormation();

    auto FormationProbability(G4double val) -> void { fFormationProbability = val; }
    auto ConversionProbability(G4double val) -> void { fConversionProbability = val; }

    auto IsApplicable(const G4ParticleDefinition&) -> G4bool override;
    auto StartTracking(G4Track* track) -> void override;
    auto AtRestDoIt(const G4Track& track, const G4Step&) -> G4VParticleChange* override;

private:
    auto GetMeanLifeTime(const G4Track& track, G4ForceCondition*) -> G4double override;

private:
    const G4ParticleDefinition* const fMuonium;
    const G4ParticleDefinition* const fAntimuonium;
    const ATarget* const fTarget;
    CLHEP::HepRandomEngine* fRandEng;

    G4double fFormationProbability;
    G4double fConversionProbability;

    G4ParticleChange fParticleChange;
};

} // namespace MACE::inline Simulation::inline Physics::inline Process

#include "MACE/Simulation/Physics/Process/MuoniumFormation.inl"
