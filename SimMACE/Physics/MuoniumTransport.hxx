#pragma once

#include "G4VContinuousProcess.hh"
#include "G4ParticleChange.hh"

#include "SimMACE/Global.hxx"
#include "SimMACE/Action/DetectorConstruction.hxx"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow" // suppress ridiculous warnings caused by TString: (const char* s) shadows CLHEP::s
#include "SimMTransport/Track.hxx"
#pragma GCC diagnostic pop

class MACE::SimMACE::Physics::MuoniumTransport final :
    public G4VContinuousProcess,
    protected MACE::SimMTransport::Track {
public:
    MuoniumTransport();
    ~MuoniumTransport() noexcept;

    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step&) override;
    G4double GetContinuousStepLimit(const G4Track& track, G4double previousStepSize, G4double currentMinimumStep, G4double& currentSafety) override;

private:
    G4ParticleChange* const fParticleChange;
    G4VPhysicalVolume* const fpTarget;
};
