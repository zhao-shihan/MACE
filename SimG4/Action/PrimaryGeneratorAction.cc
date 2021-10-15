#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

#include "SimG4/Action/PrimaryGeneratorAction.hh"
#include "SimG4/Messenger/MuonBeamMessenger.hh"

using namespace MACE::SimG4::Action;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    G4VUserPrimaryGeneratorAction(),
    fParticleGun(new G4ParticleGun(G4MuonPlus::Definition())) {
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
    Messenger::MuonBeamMessenger::Instance()->Set(this);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const G4int count = round(fPlusePeakInterval * fFlux);
    const G4double timeAtPeak = (fFirstTrueEventIDOfThisRank+event->GetEventID()) * fPlusePeakInterval;
    for (G4int i = 0; i < count; ++i) {
        fParticleGun->SetParticleTime(G4RandGauss::shoot(timeAtPeak, fPluseWidthRMS));
        fParticleGun->SetParticlePosition(G4ThreeVector(G4RandGauss::shoot(0, fBeamWidthRMS), G4RandGauss::shoot(0, fBeamWidthRMS), -1.5 * m));
        fParticleGun->SetParticleEnergy(G4RandGauss::shoot(fEnergy, fEnergySpreadRMS));
        fParticleGun->GeneratePrimaryVertex(event);
    }
}
