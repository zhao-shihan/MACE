#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "Randomize.hh"

namespace MACE::SimMACE::inline Action {

using namespace LiteralUnit::Time;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fGeneralParticleSource{},
    fPulseWidth{20_ns},
    fPrimariesForEachG4Event{10},
    fMessengerRegister{this} {}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    G4RandFlat randFlat{*G4Random::getTheEngine(), 0, fPulseWidth};
    for (G4int i{}; i < fPrimariesForEachG4Event; ++i) {
        fGeneralParticleSource.SetParticleTime(randFlat.fire());
        fGeneralParticleSource.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimMACE::inline Action
