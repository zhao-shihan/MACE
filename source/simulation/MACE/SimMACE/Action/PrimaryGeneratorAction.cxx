#include "MACE/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimMACE/Messenger/PrimaryGeneratorActionMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Event.hh"
#include "Randomize.hh"

namespace MACE::SimMACE::Action {

using namespace Utility::LiteralUnit::Frequency;
using namespace Utility::LiteralUnit::Time;

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    fSurfaceMuonGenerator(),
    fFlux(1e7_s_1),
    fRepetitionRate(50_Hz),
    fTimeWidthRMS(100_us),
    fMuonsForEachG4Event(500),
    fRepetitionID(-1) {
    Messenger::PrimaryGeneratorActionMessenger::Instance().AssignTo(this);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const auto muonsForEachReptition = fFlux / fRepetitionRate;                         // no rounding
    const auto g4EventsForEachReptition = muonsForEachReptition / fMuonsForEachG4Event; // no rounding
    fRepetitionID = event->GetEventID() / g4EventsForEachReptition;                     // rounding here

    const auto randEng = G4Random::getTheEngine();
    for (G4int i = 0; i < fMuonsForEachG4Event; ++i) {
        fSurfaceMuonGenerator.VertexTime(G4RandGauss::shoot(randEng, 0, fTimeWidthRMS));
        fSurfaceMuonGenerator.GeneratePrimaryVertex(event);
    }
}

} // namespace MACE::SimMACE::Action
