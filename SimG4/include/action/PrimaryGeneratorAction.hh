/*Shoot Muon+ current,
    energy with gaussrandom,
    same momentum derection*/

#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"


#include "SimG4Global.hh"

class MACE::SimG4::PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

private:
    G4ParticleGun* fParticleGun;
};
