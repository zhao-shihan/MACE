#pragma once

#include "G4VRestProcess.hh"
#include "G4ParticleChange.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Physics::MuoniumProduction final :
    public G4VRestProcess {
public:
    MuoniumProduction();
    ~MuoniumProduction() noexcept;

    G4VParticleChange* AtRestDoIt(const G4Track& track, const G4Step&) override;
    G4double GetMeanLifeTime(const G4Track&, G4ForceCondition*) override { return fMeanLifeTime; }

    void SetConversionProbability(G4double val) { fConversionProbability = val; }

private:
    G4ParticleChange* const fParticleChange;
    const G4double fMeanLifeTime = 1.46467 * us; // 60%
    G4double fConversionProbability = 8.3e-11;
};
