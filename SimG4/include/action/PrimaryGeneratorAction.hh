#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "SimG4Global.hh"

class MACE::SimG4::PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* event) override;

    void SetFirstPluseIDOfThisRank(G4int pluseID) { fFirstPluseIDOfThisRank = pluseID; }

    void SetFlux(G4double val) { fFlux = val; }
    void SetPlusePeakInterval(G4double val) { fPlusePeakInterval = val; }
    void SetPluseWidthRMS(G4double val) { fPluseWidthRMS = val; }
    void SetEnergy(G4double val) { fEnergy = val; }
    void SetEnergySpreadRMS(G4double val) { fEnergySpreadRMS = val; }
    void SetBeamWidthRMS(G4double val) { fBeamWidthRMS = val; }

private:
    G4ParticleGun* const fParticleGun;

    G4int    fFirstPluseIDOfThisRank;

    G4double fFlux = 1e8 / s;
    G4double fPlusePeakInterval = 10 * us;
    G4double fPluseWidthRMS = 2 * us;

    G4double fEnergy = 1.5 * MeV;
    G4double fEnergySpreadRMS = 0.05 * fEnergy;

    G4double fBeamWidthRMS = 5 * mm;
};
