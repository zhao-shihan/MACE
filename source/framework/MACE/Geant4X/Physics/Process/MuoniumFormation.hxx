#pragma once

#include "MACE/Core/Geometry/Description/Target.hxx"

#include "G4ParticleChange.hh"
#include "G4VRestProcess.hh"

namespace MACE::Geant4X::Physics::Process {

using Core::Geometry::Description::Target;

class MuoniumFormation final : public G4VRestProcess {
public:
    MuoniumFormation();
    ~MuoniumFormation() noexcept = default;
    MuoniumFormation(const MuoniumFormation&) = delete;
    MuoniumFormation& operator=(const MuoniumFormation&) = delete;

    void SetFormationProbability(G4double val) { fFormationProbability = val; }
    void SetConversionProbability(G4double val) { fConversionProbability = val; }

    G4bool IsApplicable(const G4ParticleDefinition&) override;
    void StartTracking(G4Track* track) override;
    G4VParticleChange* AtRestDoIt(const G4Track& track, const G4Step&) override;

private:
    G4double GetMeanLifeTime(const G4Track& track, G4ForceCondition*) override;

private:
    const G4ParticleDefinition* const fMuonium;
    const G4ParticleDefinition* const fAntiMuonium;
    const Target* const fTarget;
    CLHEP::HepRandomEngine* fRandEng;

    G4double fFormationProbability;
    G4double fConversionProbability;

    G4ParticleChange fParticleChange;
};

} // namespace MACE::Geant4X::Physics::Process
