#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "SimG4Global.hh"

class MACE::SimG4::PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* event) override;

private:
    G4ParticleGun* fParticleGun;

    G4double fFlux = 1e8 / s;
    G4double fPlusePeakInterval = 1 * us;
    G4double fPluseSpreadRMS = 0.2 * us;
    
    G4double fEnergy = 1.5 * MeV;
    G4double fEnergySpreadRMS = 0.05 * fEnergy;
    
    G4double fWidthRMS = 5 * mm;
};
