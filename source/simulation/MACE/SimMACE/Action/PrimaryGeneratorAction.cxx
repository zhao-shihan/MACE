#include "MACE/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimMACE/Messenger/PrimaryGeneratorActionMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Event.hh"
#include "Randomize.hh"

namespace MACE::SimMACE::inline Action {

using namespace LiteralUnit::Time;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    fSurfaceMuonGenerator(),
    fTimeWidthRMS(20_ns),
    fMuonsForEachG4Event(10) {
    PrimaryGeneratorActionMessenger::Instance().AssignTo(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    G4RandGauss randGauss = {*G4Random::getTheEngine(), 0, fTimeWidthRMS};
    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        fSurfaceMuonGenerator.Time(randGauss.fire());
        fSurfaceMuonGenerator.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimMACE::inline Action
