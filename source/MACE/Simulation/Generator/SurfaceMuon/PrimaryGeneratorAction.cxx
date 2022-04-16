#include "MACE/Simulation/Generator/SurfaceMuon/GeneratorMessenger.hxx"
#include "MACE/Simulation/Generator/SurfaceMuon/PrimaryGeneratorAction.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Event.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"

namespace MACE::Simulation::Generator::SurfaceMuon {

using namespace Utility::LiteralUnit;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    G4VUserPrimaryGeneratorAction(),
    fSurfaceMuonBeam(G4MuonPlus::Definition()),
    fFlux(1e7_s_1),
    fRepetitionRate(50_Hz),
    fTimeWidthRMS(100_us),
    fEnergy(1.5_MeV),
    fEnergySpreadRMS(0.05 * fEnergy),
    fBeamProfileRMS(5_mm),
    fVertexZ(-1.5_m),
    fMuonsForEachG4Event(500),
    fRepetitionID(-1) {
    fSurfaceMuonBeam.SetParticleMomentumDirection(CLHEP::HepZHat);
    GeneratorMessenger::Instance().SetTo(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const auto muonsForEachReptition = fFlux / fRepetitionRate;                         // no rounding
    const auto g4EventsForEachReptition = muonsForEachReptition / fMuonsForEachG4Event; // no rounding
    fRepetitionID = event->GetEventID() / g4EventsForEachReptition;                     // rounding here

    auto* const randEng = G4Random::getTheEngine();
    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        fSurfaceMuonBeam.SetParticleTime(G4RandGauss::shoot(randEng, 0, fTimeWidthRMS));
        fSurfaceMuonBeam.SetParticlePosition(G4ThreeVector(G4RandGauss::shoot(randEng, 0, fBeamProfileRMS),
                                                           G4RandGauss::shoot(randEng, 0, fBeamProfileRMS),
                                                           fVertexZ));
        fSurfaceMuonBeam.SetParticleEnergy(G4RandGauss::shoot(randEng, fEnergy, fEnergySpreadRMS));
        fSurfaceMuonBeam.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::Simulation::Generator::SurfaceMuon
