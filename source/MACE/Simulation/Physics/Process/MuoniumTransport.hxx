#pragma once

#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4ParticleChange.hh"
#include "G4SafetyHelper.hh"
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

    void SetMeanFreePath(G4double val);
    void SetManipulateEachStepOfFlight(G4bool val) { fManipulateEachStepOfFlight = val; }

    void StartTracking(G4Track* track) override;
    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step&) override;

private:
    G4double GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double&) override;
    void ProposeRandomFlight(const G4Track& track);

private:
    enum TransportCondition {
        kUnknown = -1,
        kDecaying,
        kInsideTargetVolume,
        kExitingTargetVolume,
        kExitedTargetVolume
    };

private:
    const ObserverPtr<const Target> fTarget;
    ObserverPtr<CLHEP::HepRandomEngine> fRandEng;

    G4double fMeanFreePath;
    static constexpr G4double fToleranceScale = 0.01;
    G4double fTolerance;
    G4bool fManipulateEachStepOfFlight;

    G4ParticleChange fParticleChange;
    TransportCondition fCase;
    G4bool fIsExitingTargetVolume;
};

} // namespace MACE::Simulation::Physics::Process
