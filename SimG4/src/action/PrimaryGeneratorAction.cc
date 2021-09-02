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

void MACE::SimG4::PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const G4int count = round(fPlusePeakInterval * fFlux);
    const G4double timeAtPeak = event->GetEventID() * fPlusePeakInterval;
    auto* const vertexTime = new G4double[count];
    G4RandGauss::shootArray(count, vertexTime, timeAtPeak, fPluseSpreadRMS);
    std::sort(vertexTime, vertexTime + count);
    for (G4int i = 0; i < count; ++i) {
        fParticleGun->SetParticleTime(vertexTime[i]);
        fParticleGun->SetParticlePosition(G4ThreeVector(G4RandGauss::shoot(0, fWidthRMS), G4RandGauss::shoot(0, fWidthRMS), -1.5 * m));
        fParticleGun->SetParticleEnergy(G4RandGauss::shoot(fEnergy, fEnergySpreadRMS));
        fParticleGun->GeneratePrimaryVertex(event);
    }
    delete vertexTime;
}
