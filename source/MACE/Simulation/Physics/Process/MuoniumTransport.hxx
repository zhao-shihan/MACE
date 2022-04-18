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

    void SetMeanFreePath(G4double val) { fMeanFreePath = val; }
    void SetFlightLimit(G4double val) { fFlightLimit = val; }

    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step& step) override;

private:
    void ProposeRandomFlight(const G4Track& track, const G4Step& step);

    G4double GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) override;

private:
    enum TransportCondition {
        fUnknown = -1,
        fInTargetVolume,
        fInVacuum,
        fInCondensedMatter,
    };

private:
    const ObserverPtr<const Target> fTarget;

    G4double fMeanFreePath;
    G4double fFlightLimit;

    TransportCondition fCase;
    G4ParticleChange fParticleChange;
};

} // namespace MACE::Simulation::Physics::Process
