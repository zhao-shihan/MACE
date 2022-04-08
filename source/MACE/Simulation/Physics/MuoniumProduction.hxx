#pragma once

#include "MACE/Utility/LiteralUnit.hxx"

#include "G4ParticleChange.hh"
#include "G4VRestProcess.hh"

namespace MACE::Simulation::Physics {

using namespace MACE::Utility::LiteralUnit;

class MuoniumProduction final : public G4VRestProcess {
public:
    MuoniumProduction();
    ~MuoniumProduction() noexcept = default;

    G4VParticleChange* AtRestDoIt(const G4Track& track, const G4Step&) override;
    G4double GetMeanLifeTime(const G4Track&, G4ForceCondition*) override { return fMeanLifeTime; }

    void SetMeanLifeTime(G4double val) { fMeanLifeTime = val; }
    void SetConversionProbability(G4double val) { fConversionProbability = val; }

private:
    G4ParticleChange fParticleChange;
    G4double fMeanLifeTime = 1.46467_us; // 60%
    G4double fConversionProbability = 8.3e-11;
};

} // namespace MACE::Simulation::Physics
