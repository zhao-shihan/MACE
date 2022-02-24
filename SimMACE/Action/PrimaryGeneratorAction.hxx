#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Action::PrimaryGeneratorAction final :
    public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() noexcept = default;
    void GeneratePrimaries(G4Event* event) override;

    void SetFirstTrueEventIDOfThisRank(G4int trueEventID) { fFirstTrueEventIDOfThisRank = trueEventID; }

    void SetFlux(G4double val) { fFlux = val; }
    void SetPlusePeakInterval(G4double val) { fPlusePeakInterval = val; }
    void SetPluseWidthRMS(G4double val) { fPluseWidthRMS = val; }
    void SetEnergy(G4double val) { fEnergy = val; }
    void SetEnergySpreadRMS(G4double val) { fEnergySpreadRMS = val; }
    void SetBeamWidthRMS(G4double val) { fBeamWidthRMS = val; }

private:
    G4ParticleGun fParticleGun;

    G4int    fFirstTrueEventIDOfThisRank = 0;

    G4double fFlux = 1e8_s_1;
    G4double fPlusePeakInterval = 10_us;
    G4double fPluseWidthRMS = 2_us;

    G4double fEnergy = 1.5_MeV;
    G4double fEnergySpreadRMS = 0.05 * fEnergy;

    G4double fBeamWidthRMS = 5_mm;
};
