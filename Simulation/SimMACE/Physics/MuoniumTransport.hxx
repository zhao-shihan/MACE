#pragma once

#include "Utility/ObserverPtr.hxx"
#include "Simulation/SimMACE/Action/DetectorConstruction.hxx"
#include "Simulation/SimMACE/Global.hxx"
#include "SimMTransport/Track.hxx"

#include "G4ParticleChange.hh"
#include "G4VContinuousProcess.hh"

namespace MACE::Simulation::SimMACE::Physics {

class MuoniumTransport final : public G4VContinuousProcess,
                               protected MACE::Simulation::SimMTransport::Track {
public:
    MuoniumTransport();
    ~MuoniumTransport() noexcept = default;

    G4VParticleChange* AlongStepDoIt(const G4Track& track, const G4Step&) override;
    G4double GetContinuousStepLimit(const G4Track& track, G4double previousStepSize, G4double currentMinimumStep, G4double& currentSafety) override;

private:
    G4ParticleChange fParticleChange;
};

} // namespace MACE::Simulation::SimMACE::Physics
