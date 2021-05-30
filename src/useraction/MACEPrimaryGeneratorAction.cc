#include "useraction/MACEPrimaryGeneratorAction.hh"
#include "physics/MACEMuoniumPlus.hh"

#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"

using namespace CLHEP;

MACEPrimaryGeneratorAction::MACEPrimaryGeneratorAction(G4int numberOfParticlesPerEvent) :
    G4VUserPrimaryGeneratorAction(),
    fParticleGun(new G4ParticleGun(G4MuonPlus::Definition())),
    fNumberOfParticlesPerEvent(numberOfParticlesPerEvent),
    fMessenger(new MACEPGAMessenger(this)) {}

MACEPrimaryGeneratorAction::~MACEPrimaryGeneratorAction() {
    delete fParticleGun;
}

constexpr G4double beamFlux = 8e6 / s;

void MACEPrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    for (G4int i = 0; i < fNumberOfParticlesPerEvent; ++i) {
        fParticleGun->SetParticlePosition(
            G4ThreeVector(RandGauss::shoot(0., 20 * mm), RandGauss::shoot(0., 20 * mm), -0.5 * m));
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
        fParticleGun->SetParticleTime(fNumberOfParticlesPerEvent / beamFlux * G4UniformRand());
        fParticleGun->SetParticleEnergy(RandGauss::shoot(26, 1.3) * MeV);
        fParticleGun->GeneratePrimaryVertex(event);
    }
}

