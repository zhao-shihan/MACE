#include "G4Event.hh"

#include "SimG4/Action/EventAction.hxx"
#include "SimG4/Action/PrimaryGeneratorAction.hxx"
#include "SimG4/Analysis.hxx"

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
