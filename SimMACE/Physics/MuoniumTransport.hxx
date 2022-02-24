#pragma once

#include "G4VContinuousProcess.hh"
#include "G4ParticleChange.hh"

#include "SimMACE/Global.hxx"
#include "SimMACE/Action/DetectorConstruction.hxx"
#include "SimMTransport/Track.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::Physics::MuoniumTransport final :
    public G4VContinuousProcess,
    protected MACE::SimMTransport::Track {
public:
    MuoniumTransport();
    ~MuoniumTransport() noexcept = default;

    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step&) override;
    G4double GetContinuousStepLimit(const G4Track& track, G4double previousStepSize, G4double currentMinimumStep, G4double& currentSafety) override;

private:
    G4ParticleChange fParticleChange;
    ObserverPtr<G4VPhysicalVolume> fTarget;
};
