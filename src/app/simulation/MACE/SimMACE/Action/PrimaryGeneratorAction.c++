#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Event.hh"
#include "Randomize.hh"

namespace MACE::SimMACE::inline Action {

using namespace LiteralUnit::Time;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fSurfaceMuonGenerator{},
    fTimeWidthRMS{20_ns},
    fMuonsForEachG4Event{10},
    fMessengerRegister{this} {}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    G4RandGauss randGauss = {*G4Random::getTheEngine(), 0, fTimeWidthRMS};
    for (G4int i{}; i < fMuonsForEachG4Event; ++i) {
        fSurfaceMuonGenerator.Time(randGauss.fire());
        fSurfaceMuonGenerator.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimMACE::inline Action
