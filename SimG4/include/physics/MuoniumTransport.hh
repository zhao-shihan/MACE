#pragma once

#include "G4VContinuousProcess.hh"
#include "G4ParticleChange.hh"

#include "SimG4Global.hh"
#include "detector/DetectorConstruction.hh"
#include "Track.hh"

class MACE::SimG4::Physics::MuoniumTransport : public G4VContinuousProcess, protected MACE::SimMTransport::Track {
public:
    MuoniumTransport(const G4String& name = "MuoniumTransport", G4ProcessType aType = fTransportation);
    ~MuoniumTransport();

    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step&) override;
    G4double GetContinuousStepLimit(const G4Track& track, G4double previousStepSize, G4double currentMinimumStep, G4double& currentSafety) override;

private:
    G4ParticleChange* const fParticleChange;
    G4VPhysicalVolume* const fpTarget;
};