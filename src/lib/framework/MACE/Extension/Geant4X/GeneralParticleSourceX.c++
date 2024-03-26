#include "MACE/Extension/Geant4X/GeneralParticleSourceX.h++"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "Randomize.hh"

namespace MACE::inline Extension::Geant4X {

GeneralParticleSourceX::GeneralParticleSourceX() :
    G4GeneralParticleSource{},
    fPulseWidth{},
    fMessengerRegister{this} {}

auto GeneralParticleSourceX::GeneratePrimaryVertex(G4Event* event) -> void {
    const auto nBefore{event->GetNumberOfPrimaryVertex()};
    G4GeneralParticleSource::GeneratePrimaryVertex(event);
    const auto nAfter{event->GetNumberOfPrimaryVertex()};
    auto& rand{*G4Random::getTheEngine()};
    for (auto k{nBefore}; k < nAfter; ++k) {
        auto& primary{*event->GetPrimaryVertex(k)};
        primary.SetT0(primary.GetT0() + rand.flat() * fPulseWidth);
    }
}

} // namespace MACE::inline Extension::Geant4X
