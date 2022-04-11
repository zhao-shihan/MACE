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
    fSurfaceMuonsOfThisG4Event(500),
    fRepetitionID(-1) {
    fSurfaceMuonBeam.SetParticleMomentumDirection(CLHEP::HepZHat);
    GeneratorMessenger::Instance().SetTo(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const auto muonsForEachReptition = fFlux / fRepetitionRate;                                      // no rounding
    const auto g4EventsForEachReptition = muonsForEachReptition / fSurfaceMuonsOfThisG4Event.size(); // no rounding
    fRepetitionID = event->GetEventID() / g4EventsForEachReptition;                                  // rounding here

    for (auto&& [time, position, energy] : fSurfaceMuonsOfThisG4Event) {
        time = G4RandGauss::shoot(0, fTimeWidthRMS);
        position.set(G4RandGauss::shoot(0, fBeamProfileRMS),
                     G4RandGauss::shoot(0, fBeamProfileRMS),
                     fVertexZ);
        energy = G4RandGauss::shoot(fEnergy, fEnergySpreadRMS);
    }
    for (auto&& [time, position, energy] : std::as_const(fSurfaceMuonsOfThisG4Event)) {
        fSurfaceMuonBeam.SetParticleTime(time);
        fSurfaceMuonBeam.SetParticlePosition(position);
        fSurfaceMuonBeam.SetParticleEnergy(energy);
        fSurfaceMuonBeam.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::Simulation::Generator::SurfaceMuon
