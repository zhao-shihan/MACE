#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

#include "action/PrimaryGeneratorAction.hh"

MACE::SimG4::PrimaryGeneratorAction::PrimaryGeneratorAction() :
    G4VUserPrimaryGeneratorAction(),
    fParticleGun(new G4ParticleGun(G4MuonPlus::Definition())) {
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
}

MACE::SimG4::PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

constexpr G4double beamFlux = 8e6 / s;
constexpr G4double beamWidthRMS = 5 * mm;
constexpr G4double meanEnergy = 1.5 * MeV;
constexpr G4double energySpreadRMS = 5 * perCent;

void MACE::SimG4::PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    constexpr G4double avgTimeInterval = 1 / beamFlux;
    fParticleGun->SetParticleTime(avgTimeInterval * (event->GetEventID() + G4RandFlat::shoot()));
    fParticleGun->SetParticlePosition(G4ThreeVector(G4RandGauss::shoot(0, beamWidthRMS), G4RandGauss::shoot(0, beamWidthRMS), -1.5 * m));
    fParticleGun->SetParticleEnergy(G4RandGauss::shoot(meanEnergy, energySpreadRMS * meanEnergy));
    fParticleGun->GeneratePrimaryVertex(event);
}

