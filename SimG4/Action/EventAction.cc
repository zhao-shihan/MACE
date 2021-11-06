#include "G4Event.hh"

#include "SimG4/Action/EventAction.hh"
#include "SimG4/Action/PrimaryGeneratorAction.hh"
#include "SimG4/Analysis.hh"

using namespace MACE::SimG4::Action;

EventAction::EventAction() :
    G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* event) {
    Analysis::Instance()->SetTrueEventID(fFirstTrueEventIDOfThisRank + event->GetEventID());
}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance()->WriteEvent();
}
