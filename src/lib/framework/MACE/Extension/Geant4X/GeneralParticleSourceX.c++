#include "MACE/Extension/Geant4X/GeneralParticleSourceX.h++"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "Randomize.hh"

namespace MACE::inline Extension::Geant4X {

GeneralParticleSourceX::GeneralParticleSourceX() :
    G4GeneralParticleSource{},
    fNVertex{1},
    fPulseWidth{},
    fMessengerRegister{this} {}

auto GeneralParticleSourceX::GeneratePrimaryVertex(G4Event* event) -> void {
    auto& rand{*G4Random::getTheEngine()};
    const auto t0{GetParticleTime()};
    for (int i{}; i < fNVertex; ++i) {
        SetParticleTime(t0 + rand.flat() * fPulseWidth);
        G4GeneralParticleSource::GeneratePrimaryVertex(event);
    }
    SetParticleTime(t0);
}

} // namespace MACE::inline Extension::Geant4X
