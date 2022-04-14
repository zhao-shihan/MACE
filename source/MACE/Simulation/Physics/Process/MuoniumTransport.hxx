#pragma once

#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4ParticleChange.hh"
#include "G4VContinuousProcess.hh"

namespace MACE::Simulation::Physics::Process {

using Core::Geometry::Description::Target;
using Utility::ObserverPtr;

class MuoniumTransport final : public G4VContinuousProcess {
public:
    MuoniumTransport();
    ~MuoniumTransport() noexcept = default;
    MuoniumTransport(const MuoniumTransport&) = delete;
    MuoniumTransport& operator=(const MuoniumTransport&) = delete;

    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step& step) override;

private:
    G4double GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) override;
    void ProposeRandomFlight(const G4double& initialTime,
                             const G4ThreeVector& initialPosition,
                             const G4double& initialVelocity,
                             const G4ThreeVector& initialDirection,
                             const G4double& temperature,
                             const G4double& trueStepLimit);

private:
    const ObserverPtr<const Target> fTarget;

    G4ParticleChange fParticleChange;
    G4double fMeanFreePath;
    G4double fStepLimit;
    G4double fVacuumStepScale;

    G4int fCase;
};

} // namespace MACE::Simulation::Physics::Process
