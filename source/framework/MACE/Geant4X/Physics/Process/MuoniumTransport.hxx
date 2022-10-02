#pragma once

#include "MACE/Core/Geometry/Description/Target.hxx"

#include "G4ParticleChange.hh"
#include "G4VContinuousProcess.hh"

namespace MACE::Geant4X::Physics::Process {

using Core::Geometry::Description::Target;

class MuoniumTransport final : public G4VContinuousProcess {
public:
    MuoniumTransport();
    ~MuoniumTransport() noexcept = default;
    MuoniumTransport(const MuoniumTransport&) = delete;
    MuoniumTransport& operator=(const MuoniumTransport&) = delete;

    void SetMeanFreePath(G4double val) { fMeanFreePath = val; }
    void SetManipulateAllSteps(G4bool val) { fManipulateAllSteps = val; }

    G4bool IsApplicable(const G4ParticleDefinition&) override;
    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step&) override;

private:
    G4double GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double&) override;
    void ProposeRandomFlight(const G4Track& track);

private:
    enum class TransportStatus {
        Unknown = -1,
        Decaying,
        InsideTargetVolume,
        ExitingTargetVolume,
        OutsideTargetVolume
    };

private:
    const Target* const fTarget;

    G4double fMeanFreePath;
    G4bool fManipulateAllSteps;

    G4ParticleChange fParticleChange;
    TransportStatus fTransportStatus;
    G4bool fIsExitingTargetVolume;
};

} // namespace MACE::Geant4X::Physics::Process
