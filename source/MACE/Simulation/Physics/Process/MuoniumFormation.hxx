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

    G4VParticleChange* AtRestDoIt(const G4Track& track, const G4Step&) override;
    G4double GetMeanLifeTime(const G4Track&, G4ForceCondition*) override { return fMeanLifeTime; }

    void SetMeanLifeTime(G4double val) { fMeanLifeTime = val; }
    void SetConversionProbability(G4double val) { fConversionProbability = val; }

private:
    const ObserverPtr<const Target> fTarget;

    G4ParticleChange fParticleChange;
    G4double fMeanLifeTime;
    G4double fConversionProbability;
};

} // namespace MACE::Simulation::Physics::Process
