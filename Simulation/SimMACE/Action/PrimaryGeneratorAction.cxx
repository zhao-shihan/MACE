#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Messenger/PrimaryGeneratorMessenger.hxx"

using namespace MACE::SimMACE::Action;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    G4VUserPrimaryGeneratorAction(),
    fSurfaceMuonBeam(G4MuonPlus::Definition()),
    fRepetitionID(-1) {
    fSurfaceMuonBeam.SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
    PrimaryGeneratorMessenger::Instance();
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const auto muonsForEachReptition = fFlux / fRepetitionRate; // no rounding
    const auto g4EventsForEachReptition = muonsForEachReptition / fMuonsForEachG4Event; // no rounding
    fRepetitionID = event->GetEventID() / g4EventsForEachReptition; // rounding here

    std::vector<std::tuple<G4double, G4ThreeVector, G4double>> muonStates(fMuonsForEachG4Event);
    auto* const randEngine = G4Random::getTheEngine();
    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        muonStates[i] = std::make_tuple(
            G4RandGauss::shoot(randEngine, 0, fTimeWidthRMS),
            G4ThreeVector(
                G4RandGauss::shoot(randEngine, 0, fBeamProfileRMS),
                G4RandGauss::shoot(randEngine, 0, fBeamProfileRMS),
                -1.5_m),
            G4RandGauss::shoot(randEngine, fEnergy, fEnergySpreadRMS));
    }

    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        const auto& [time, position, energy] = muonStates[i];
        fSurfaceMuonBeam.SetParticleTime(time);
        fSurfaceMuonBeam.SetParticlePosition(position);
        fSurfaceMuonBeam.SetParticleEnergy(energy);
        fSurfaceMuonBeam.GeneratePrimaryVertex(event);
    }
}
