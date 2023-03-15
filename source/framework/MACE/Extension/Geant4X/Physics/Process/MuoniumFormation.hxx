#pragma once

#include "MACE/Extension/Geant4X/Physics/Messenger/MuoniumPhysicsMessenger.hxx"
#include "MACE/Extension/Geant4X/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/Extension/Geant4X/Physics/TargetForMuoniumPhysics.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4MuonPlus.hh"
#include "G4ParticleChange.hh"
#include "G4VRestProcess.hh"

#include "gsl/gsl"

#include <limits>

namespace MACE::inline Extension::Geant4X::Physics::Process {

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
    const G4ParticleDefinition* const fAntiMuonium;
    const ATarget* const fTarget;
    CLHEP::HepRandomEngine* fRandEng;

    G4double fFormationProbability;
    G4double fConversionProbability;

    G4ParticleChange fParticleChange;
};

} // namespace MACE::inline Extension::Geant4X::Physics::Process

#include "MACE/Extension/Geant4X/Physics/Process/MuoniumFormation.inl"
