#include "G4Event.hh"

#include "action/EventAction.hh"
#include "action/PrimaryGeneratorAction.hh"
#include "Analysis.hh"

using namespace MACE::SimG4;

EventAction::EventAction() :
    G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* event) {
    Analysis::Instance()->SetPluseID(fFirstPluseIDOfThisRank + event->GetEventID());
}

void EventAction::EndOfEventAction(const G4Event*) {
    Analysis::Instance()->Fill();
}
