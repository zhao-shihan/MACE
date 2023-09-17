#pragma once

#include "MACE/Simulation/Physics/Messenger/MuoniumPhysicsMessenger.h++"
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

namespace MACE::inline Simulation::Physics::inline Process {

template<TargetForMuoniumPhysics ATarget>
class MuoniumFormation final : public NonMoveableBase,
                               public G4VRestProcess {
public:
    MuoniumFormation();

    void FormationProbability(G4double val) { fFormationProbability = val; }
    void ConversionProbability(G4double val) { fConversionProbability = val; }

    G4bool IsApplicable(const G4ParticleDefinition&) override;
    void StartTracking(G4Track* track) override;
    G4VParticleChange* AtRestDoIt(const G4Track& track, const G4Step&) override;

private:
    G4double GetMeanLifeTime(const G4Track& track, G4ForceCondition*) override;

private:
    const G4ParticleDefinition* const fMuonium;
    const G4ParticleDefinition* const fAntimuonium;
    const ATarget* const fTarget;
    CLHEP::HepRandomEngine* fRandEng;

    G4double fFormationProbability;
    G4double fConversionProbability;

    G4ParticleChange fParticleChange;
};

} // namespace MACE::inline Simulation::Physics::inline Process

#include "MACE/Simulation/Physics/Process/MuoniumFormation.inl"
