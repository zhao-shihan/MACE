#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Messenger/MuonBeamMessenger.hxx"

using namespace MACE::SimMACE::Action;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    G4VUserPrimaryGeneratorAction(),
    fParticleGun(G4MuonPlus::Definition()) {
    fParticleGun.SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
    Messenger::MuonBeamMessenger::Instance().Set(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const G4int count = round(fPlusePeakInterval * fFlux);
    const G4double timeAtPeak = (fFirstTrueEventIDOfThisRank+event->GetEventID()) * fPlusePeakInterval;
    for (G4int i = 0; i < count; ++i) {
        fParticleGun.SetParticleTime(G4RandGauss::shoot(timeAtPeak, fPluseWidthRMS));
        fParticleGun.SetParticlePosition(G4ThreeVector(G4RandGauss::shoot(0, fBeamWidthRMS), G4RandGauss::shoot(0, fBeamWidthRMS), -1.5 * m));
        fParticleGun.SetParticleEnergy(G4RandGauss::shoot(fEnergy, fEnergySpreadRMS));
        fParticleGun.GeneratePrimaryVertex(event);
    }
}
