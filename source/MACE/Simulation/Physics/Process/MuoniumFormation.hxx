#pragma once

#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4ParticleChange.hh"
#include "G4VRestProcess.hh"

namespace MACE::Simulation::Physics::Process {

using Core::Geometry::Description::Target;
using Utility::ObserverPtr;

class MuoniumFormation final : public G4VRestProcess {
public:
    MuoniumFormation();
    ~MuoniumFormation() noexcept = default;
    MuoniumFormation(const MuoniumFormation&) = delete;
    MuoniumFormation& operator=(const MuoniumFormation&) = delete;

    G4VParticleChange* AtRestDoIt(const G4Track& track, const G4Step&) override;

    void SetFormationProbability(G4double val) { fFormationProbability = val; }
    void SetConversionProbability(G4double val) { fConversionProbability = val; }

private:
    G4double GetMeanLifeTime(const G4Track& track, G4ForceCondition*) override;

private:
    const ObserverPtr<const Target> fTarget;
    const ObserverPtr<G4ParticleDefinition> fMuonium;
    const ObserverPtr<G4ParticleDefinition> fAntiMuonium;

    G4double fFormationProbability;
    G4double fConversionProbability;

    G4ParticleChange fParticleChange;
};

} // namespace MACE::Simulation::Physics::Process
