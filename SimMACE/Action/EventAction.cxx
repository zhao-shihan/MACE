#include "G4Event.hh"

#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE::Action;

void EventAction::BeginOfEventAction(const G4Event* event) {
    Analysis::Instance().SetTrueEventID(fFirstTrueEventIDOfThisRank + event->GetEventID());
}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance().WriteEvent();
}
