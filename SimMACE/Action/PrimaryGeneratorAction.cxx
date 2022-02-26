#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/Messenger/PrimaryGeneratorMessenger.hxx"

using namespace MACE::SimMACE::Action;

PrimaryGeneratorAction::PrimaryGeneratorAction(ObserverPtr<const EventAction> eventAction) :
    G4VUserPrimaryGeneratorAction(),
    fEventAction(eventAction),
    fParticleGun(G4MuonPlus::Definition()),
    fRepetitionID(-1) {
    fParticleGun.SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
    Messenger::PrimaryGeneratorMessenger::Instance().Set(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const auto muonsPerReptition = fFlux / fRepetitionRate;
    const auto g4EventsPerReptition = muonsPerReptition / fMuonsPerG4Event;

    fRepetitionID = fEventAction->GetTrueEventID() / g4EventsPerReptition;
    const auto meanTime = fRepetitionID / fRepetitionRate;

    auto* const randEngine = G4Random::getTheEngine();
    for (G4int i = 0; i < fMuonsPerG4Event; ++i) {
        fParticleGun.SetParticleTime(G4RandGauss::shoot(randEngine, meanTime, fTimeWidthRMS));
        fParticleGun.SetParticlePosition(G4ThreeVector(G4RandGauss::shoot(randEngine, 0, fBeamProfileRMS), G4RandGauss::shoot(randEngine, 0, fBeamProfileRMS), -1.5_m));
        fParticleGun.SetParticleEnergy(G4RandGauss::shoot(randEngine, fEnergy, fEnergySpreadRMS));
        fParticleGun.GeneratePrimaryVertex(event);
    }
}
