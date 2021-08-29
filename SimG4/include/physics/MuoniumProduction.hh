#pragma once

#include "G4VRestProcess.hh"
#include "G4ParticleChange.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Physics::MuoniumProduction : public G4VRestProcess {
public:
    MuoniumProduction(const G4String& name = "MuoniumProduction", G4ProcessType aType = fElectromagnetic);
    ~MuoniumProduction();

    G4VParticleChange* AtRestDoIt(const G4Track& track, const G4Step&) override;
    G4double GetMeanLifeTime(const G4Track&, G4ForceCondition*) override { return fMeanLifeTime; }

private:
    G4ParticleChange* const fParticleChange;
    const G4double fMeanLifeTime = 1.46467 * us; // 60%
};
